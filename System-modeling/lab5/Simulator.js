'use strict'

const { round, getRandomWithProbability, selectNextByPriority } = require('./utils')


module.exports = class Simulator {

    constructor(data, simulatorParams, maxNumOfEvents=Infinity) {
        this.d = data
        this.maxNumOfEvents = maxNumOfEvents
        Object.assign(this, simulatorParams)

        // For the cars task
        this.numOfQchanges = 0
    }

    start() {
        let numOfEvents = 0
        const initialProcessor = this.processors[0].pr
        const initialName = initialProcessor.name
        this.d.taskCreationTime[initialName] = this.d.initialTime ? this.d.initialTime : 0

        while (true) {
            // Stop the loop if the max number of events is reached
            if (this.maxNumOfEvents <= numOfEvents) break

            const {
                name: minCompletionTimeName,
                value: minCompletionTimeValue
            } = this.minTaskCompletionTimes()

            // Stop the loop if no events will occur before timeLimit
            if (this.d.taskCreationTime[initialName] > this.d.timeLimit &&
                minCompletionTimeValue > this.d.timeLimit)
                break

            if (this.d.taskCreationTime[initialName] < minCompletionTimeValue) {
                initialProcessor.create()
                ++numOfEvents
            } else {
                // Get a processor with minimum completion time
                const { pr: processor, next: nextNames, nextProb, nextByTypes } =
                    this.processors.filter(x => x.name === minCompletionTimeName)[0]
                const taskId = processor.complete()
                ++numOfEvents

                // Check if the processor's output should go to another processors
                if (nextNames && this.maxNumOfEvents > numOfEvents) {
                    this.processWithNextProcessor(nextNames, nextProb, nextByTypes, taskId, processor)
                    ++numOfEvents
                } else
                    processor.desposed()
            }

            if (this.is4CarsTask)
                this.checkTheNeed2ChangeQ()
        }

        this.stats()
        const stats = []
        this.processors.forEach(processor => {
            const pr = processor.pr
            stats.push({
                name: pr.name,
                created: pr.created,
                completed: pr.completed,
                failed: pr.failed,
                failureProb: pr.calcFailureProbability(),
                avgQueueLen: pr.calcAvgQueueLen(),
                maxQueueLen: pr.maxQueueLen,
                avgCPUload: pr.avgCPUload(),
                maxCPUload: pr.maxCPUload,
                avgLeftTime: pr.calcAvgLeftTime(),
                avgVisitTime: pr.calcAvgVisitTime(),
                queueChanges: this.numOfQchanges
            })
        })
        return stats
    }

    /**
     * Process the task with the next processor that is randomly chosen by
     * probabilities from the next processor's list. It's possible (if the sum
     * of probalilities < 1) that there will be no next process
     * @param {*} nextNames - Names of possible next processors
     * @param {*} nextProb - Probabilities to choose any of the next processors
     */
    processWithNextProcessor(nextNames, nextProb, nextByTypes, taskId, processor) {
        if (nextByTypes)
            // Choose the next task by types of tasks
            this.processWithNextProcessorByType(nextNames, nextByTypes, taskId)
        else
            // Choose the next task by probabilities
            this.processWithNextProcessorByProb(nextNames, nextProb, processor)
    }

    processWithNextProcessorByType(nextNames, nextByTypes, taskId) {
        const index = nextByTypes.indexOf(taskId)
        const nextName = nextNames[index]

        this.d.taskCreationTime[nextName] = this.d.time
        const nextPr = this.getNextProcessor(nextName)
        nextPr.create()

    }

    processWithNextProcessorByProb(nextNames, nextProb, processor) {
        const nextIndex = nextProb ?
            getRandomWithProbability(nextProb, nextNames.length) :
            selectNextByPriority(nextNames, this.processors)

        // If the sum of probabilities < 1 it's possible that there will be no
        // next process
        if (nextIndex < nextNames.length) {
            const nextName = nextNames[nextIndex]
            // Move time of creation for the next processor to the current time
            this.d.taskCreationTime[nextName] = this.d.time
            const nextPr = this.getNextProcessor(nextName)
            nextPr.create()
        } else
            processor.desposed()
    }

    /**
     * Finds the smallest task completion time for all available Processors
     * instances
     * @returns {{name: String, value: number }}
     * name - Name of the process with smallest completion time
     * value - smallest completion time itself
     */
    minTaskCompletionTimes() {
        let minName = ''
        let minValue = Infinity

        for (const key in this.d.taskCompletionTimes) {
            const times = []
            this.d.taskCompletionTimes[key].forEach(obj => times.push(obj.time))

            if (minValue > Math.min(...times)) {
                minValue = Math.min(...times)
                minName = key
            }
        }
        return { name: minName, value: minValue }
    }

    /**
    * @typedef {Object} ProcessorItem
    * @property {String} name - Name of the current processor
    * @property {Processor} pr - Instance of the Processor class
    * @property {String} next - Name of the next processor
    */
    /**
     * Returns next processor from the this.processors list
     * @param {ProcessorItem} next - Next processor
     */
    getNextProcessor(name) {
        const next = this.processors.filter(x => x.name === name)[0]
        return next.pr
    }

    checkTheNeed2ChangeQ() {
        for (let i = 1; i < this.processors.length; i++) {
            for (let j = 1; j < this.processors.length; j++) {
                if (this.processors[i].pr.queue.length - this.processors[j].pr.queue.length > 1) {
                    this.processors[i].pr.queue.shift()
                    this.processors[j].pr.queue.push(0)

                    this.processors[i].pr.createdTimes.pop()
                    this.processors[j].pr.createdTimes.push(this.d.time)

                    this.numOfQchanges++
                }
            }
        }
    }

    /**
     * Print statistics for all available Processor instances
     */
    stats() {
        if (!this.showLogs) return
        console.log(`
           ===========================`)
        this.processors.forEach(processor => {
            const pr = processor.pr

            // Don't show unused processors
            if (pr.avgCPUload()) {
                console.log(`
                \x1b[35mName                        ${pr.name}\x1b[0m
                \x1b[31mFailed                      ${pr.failed}\x1b[0m`)

                pr.types.appearProbs.forEach((_, i) => {
                    console.log(
                        `                \x1b[36mCreated   of type #${i}        ${pr.created[i]}\x1b[0m`)
                })
                pr.types.appearProbs.forEach((_, i) => {
                    console.log(
                        `                \x1b[32mCompleted of type #${i}        ${pr.completed[i]}\x1b[0m`)
                })

                console.log(`
                \x1b[33mFailure probability         ${round(pr.calcFailureProbability(), 4)}%
                Avg queue length            ${round(pr.calcAvgQueueLen())}
                Max queue length            ${pr.maxQueueLen}
                Avg cpu load                ${round(pr.avgCPUload())}%
                Max cpu load                ${pr.maxCPUload} cores
                Avg tm btw completions      ${round(pr.calcAvgLeftTime())}
                Avg existence time          ${round(pr.calcAvgVisitTime())}\x1b[0m
                `)
            }
        })

        // For the cars task
        if (this.is4CarsTask)
            console.log(`
                \x1b[33mQueue changes    ${this.numOfQchanges}\x1b[0m
                `)
    }
}
