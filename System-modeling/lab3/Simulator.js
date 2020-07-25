'use strict'

const { round, getRandomWithProbability } = require('./utils')


module.exports = class Simulator {

    constructor(data, simulatorParams) {
        this.d = data
        Object.assign(this, simulatorParams)
    }

    start() {
        const initialProcessor = this.processors[0].pr
        const initialName = initialProcessor.name

        while (true) {
            let {
                name: minCompletionTimeName,
                value: minCompletionTimeValue
            } = this.minTaskCompletionTimes()

            // Stop loop if no events will occur before timeLimit
            if (this.d.taskCreationTime[initialName] > this.d.timeLimit &&
                minCompletionTimeValue > this.d.timeLimit)
                break

            if (this.d.taskCreationTime[initialName] < minCompletionTimeValue) {
                initialProcessor.create()
            } else {
                // Get a processor with minimum completion time
                const { pr: processor, next: nextNames, nextProb } =
                    this.processors.filter(x => x.name === minCompletionTimeName)[0]
                processor.complete()

                // Check if the processor's output should go to another processors
                if (nextNames)
                    this.processWithNextProcessor(nextNames, nextProb, processor)
                else
                    processor.desposed()
            }
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
                failureProb: round(pr.calcFailureProbability()),
                avgQueueLen: round(pr.calcAvgQueueLen()),
                maxQueueLen: pr.maxQueueLen,
                avgCPUload: round(pr.avgCPUload()),
                maxCPUload: pr.maxCPUload
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
    processWithNextProcessor(nextNames, nextProb, processor) {
        const nextIndex = getRandomWithProbability(nextProb)

        // If the sum of probabilities < 1 it's possible that there will be no
        // next process
        if (nextIndex < nextNames.length) {
            const nextName = nextNames[nextIndex]
            // Move time of creation for the next processor to the current time
            this.d.taskCreationTime[nextName] = this.d.time
            const processor = this.getNextProcessor(nextName).pr
            processor.create()
        } else {
            processor.desposed()
        }
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
            const times = this.d.taskCompletionTimes[key]

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
        return next
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
            if (pr.avgCPUload())
                console.log(`
                \x1b[35mName             ${pr.name}\x1b[0m
                \x1b[36mCreated          ${pr.created}\x1b[0m
                \x1b[32mCompleted        ${pr.completed}\x1b[0m
                \x1b[31mFailed           ${pr.failed}\x1b[0m

                \x1b[33mFailure prob.    ${round(pr.calcFailureProbability())}%
                Avg queue len.   ${round(pr.calcAvgQueueLen())}
                Max queue len.   ${pr.maxQueueLen}
                Avg cpu load     ${round(pr.avgCPUload())}%
                Max cpu load     ${pr.maxCPUload} cores\x1b[0m
                `)
        })
    }
}
