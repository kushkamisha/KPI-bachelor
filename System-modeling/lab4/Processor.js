'use strict'

const { random, round, sum, average, getRandomWithProbability } = require('./utils')


module.exports = class Processor {

    constructor(data, params, name) {
        Object.assign(this, params)

        // Types of tasks
        this.types = params.types ?
            params.types :
            {
                appearProbs: [1],
                timesAvgToComplete: [params.timeAvgToComplete]
            }

        this.d = data
        this.name = name

        this.d.taskCreationTime[this.name] = 0
        this.d.taskCompletionTimes[this.name] = []

        // Variables for statistics
        this.queue = new Array(this.initialQlen ? this.initialQlen : 0).fill(0)
        this.failed =
        this.maxQueueLen =
        this.maxCPUload =
        this.cpuLoadTime =
        this.timeOfQueueChanges =
        this.sumOfQueueLenghts = 
        this.previousLeftTime = 0
        this.diffsInLeftTimes = []
        this.createdTimes = new Array(this.queue.length).fill(0)
        this.visitTimes = []
        this.created = new Array(this.types.appearProbs.length).fill(0)
        this.completed = new Array(this.types.appearProbs.length).fill(0)
        this.distribution = this.distribution ? this.distribution : 'exp'
    }

    create() {
        // Move time to the event
        this.d.time = this.d.taskCreationTime[this.name]
        this.d.taskCreationTime[this.name] = this.d.time + this.rand(this.timeAvgToCreate)

        const nextTaskId = getRandomWithProbability(this.types.appearProbs, this.types.appearProbs.length)
        this.created[nextTaskId]++

        if (this.d.taskCompletionTimes[this.name].length < this.numOfCores) {
            const timeToComplete = this.rand(this.types.timesAvgToComplete[nextTaskId])
            this.d.taskCompletionTimes[this.name].push({ time: this.d.time + timeToComplete, taskId: nextTaskId })
            this.event('create', nextTaskId)
            // Statistics
            this.cpuLoad(timeToComplete)
        } else if (this.queue.length < this.queueLimit)
            this.event('to queue', nextTaskId)
        else
            this.event('failure')
    }

    complete() {
        // Move time to the event
        const times = []
        this.d.taskCompletionTimes[this.name].forEach(obj => times.push(obj.time))
        this.d.time = Math.min(...times)

        // If tasks in the queue - create new task
        if (this.queue.length !== 0) this.getTaskFromQueue()

        return this.removeCompletedTaskTime()
    }

    getTaskFromQueue() {
        this.queueLenChanges()
        const nextTaskId = this.queue.shift()
        const timeToComplete = this.rand(this.types.timesAvgToComplete[nextTaskId])
        this.d.taskCompletionTimes[this.name].push({ time: this.d.time + timeToComplete, taskId: nextTaskId })
        // Statistics
        this.cpuLoad(timeToComplete)
    }

    removeCompletedTaskTime() {
        let indexOfCurrTime = undefined
        let taskId
        this.d.taskCompletionTimes[this.name].forEach((obj, i) => {
            if (obj.time === this.d.time) {
                indexOfCurrTime = i
                taskId = obj.taskId
            }
        })

        this.d.taskCompletionTimes[this.name].splice(indexOfCurrTime, 1)

        this.event('complete', taskId)

        return taskId
    }

    event(type, taskId = '-') {
        this.updateStats(type, taskId)
        this.log(type, taskId)
    }

    log(type, taskId) {
        if (!this.showLogs) return
        console.log(`
            Name:           ${this.name}
            Time:           ${round(this.d.time, 3)}
            Busy cores:     ${this.d.taskCompletionTimes[this.name].length}
            Queue length:   ${this.queue.length}
            Task type:      ${taskId}
            Type:           ${type}`)
    }

    desposed() {
        if (!this.showLogs) return
        console.log(`
               \x1b[35m${this.name} - desposed\x1b[0m`)
    }

    updateStats(type, taskId) {
        switch(type) {
            case 'create':
                if (this.d.taskCompletionTimes[this.name].length > this.maxCPUload)
                    this.maxCPUload = this.d.taskCompletionTimes[this.name].length
                // For the cars task
                this.createdTimes.push(this.d.time)
                break
            case 'complete':
                this.completed[taskId]++
                // For the cars task
                this.diffsInLeftTimes.push(this.d.time - this.previousLeftTime)
                this.previousLeftTime = this.d.time
                this.visitTimes.push(this.d.time - this.createdTimes.shift())
                break
            case 'to queue':
                this.queueLenChanges()
                this.queue.push(taskId)
                if (this.queue.length > this.maxQueueLen)
                    this.maxQueueLen = this.queue.length
                // For the cars task
                this.createdTimes.push(this.d.time)
                break
            case 'failure':
                this.failed++
                break
        }
    }

    rand(params) {
        return Array.isArray(params) ?
            random[this.distribution](...params) :
            random[this.distribution](params)
    }

    /*********************
     ** Statistics zone **
     ********************/

    queueLenChanges() {
        this.sumOfQueueLenghts += (this.d.time - this.timeOfQueueChanges) * this.queue.length
        this.timeOfQueueChanges = this.d.time
    }

    cpuLoad(timeToComplete) {
        if (this.d.time + timeToComplete < this.d.timeLimit)
            this.cpuLoadTime += timeToComplete
        else
            this.cpuLoadTime += this.d.timeLimit - this.d.time
    }

    avgCPUload() {
        return this.numOfCores === Infinity ?
            -666 : // just to return smth, because otherwise no logs will be shown
            this.cpuLoadTime / this.d.timeLimit / this.numOfCores * 100
    }

    calcAvgQueueLen() {
        this.queueLenChanges()
        return this.sumOfQueueLenghts / this.d.timeLimit
    }

    calcFailureProbability() {
        const created = sum(this.created) === 0 ? 1 : sum(this.created)
        return this.failed / created * 100
    }

    calcAvgLeftTime() {
        return average(this.diffsInLeftTimes)
    }

    calcAvgVisitTime() {
        return average(this.visitTimes)
    }
}
