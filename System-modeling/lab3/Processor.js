'use strict'

const { randomExp, round } = require('./utils')


module.exports = class Processor {

    constructor(data, params, name) {
        Object.assign(this, params)

        this.d = data
        this.name = name

        this.d.taskCreationTime[this.name] = 0
        this.d.taskCompletionTimes[this.name] = []

        // Variables for statistics
        this.queue =
        this.created =
        this.completed =
        this.failed =
        this.maxQueueLen =
        this.maxCPUload =
        this.cpuLoadTime =
        this.timeOfQueueChanges =
        this.sumOfQueueLenghts = 0
    }

    create() {
        // Move time to the event
        this.d.time = this.d.taskCreationTime[this.name]
        this.d.taskCreationTime[this.name] = this.d.time + randomExp(this.timeAvgToCreate)
        this.created++

        if (this.d.taskCompletionTimes[this.name].length < this.numOfCores) {
            const timeToComplete = randomExp(this.timeAvgToComplete)
            this.d.taskCompletionTimes[this.name].push(this.d.time + timeToComplete)
            this.event('create')
            // Statistics
            this.cpuLoad(timeToComplete)
        } else if (this.queue < this.queueLimit)
            this.event('to queue')
        else
            this.event('failure')
    }

    complete() {
        // Move time to the event
        this.d.time = Math.min(...this.d.taskCompletionTimes[this.name])

        // If tasks in the queue - create new task
        if (this.queue !== 0) this.getTaskFromQueue()

        // Remove completed task time
        this.d.taskCompletionTimes[this.name].splice(
            this.d.taskCompletionTimes[this.name].indexOf(this.d.time), 1)
        this.event('complete')
    }

    getTaskFromQueue() {
        this.queueLenChanges()
        this.queue--
        const timeToComplete = randomExp(this.timeAvgToComplete)
        this.d.taskCompletionTimes[this.name].push(this.d.time + timeToComplete)
        // Statistics
        this.cpuLoad(timeToComplete)
    }

    event(type) {
        this.updateStats(type)
        this.log(type)
    }

    log(type) {
        if (!this.showLogs) return
        console.log(`
            Name:           ${this.name}
            Time:           ${round(this.d.time, 3)}
            Busy cores:     ${this.d.taskCompletionTimes[this.name].length}
            Queue length:   ${this.queue}
            Type:           ${type}`)
    }

    desposed() {
        if (!this.showLogs) return
        console.log(`
               \x1b[35m${this.name} - desposed\x1b[0m`)
    }

    updateStats(type) {
        switch(type) {
            case 'create':
                if (this.d.taskCompletionTimes[this.name].length > this.maxCPUload)
                    this.maxCPUload = this.d.taskCompletionTimes[this.name].length
                break
            case 'complete':
                this.completed++
                break
            case 'to queue':
                this.queueLenChanges()
                ++this.queue
                if (this.queue > this.maxQueueLen)
                    this.maxQueueLen = this.queue
                break
            case 'failure':
                this.failed++
                break
        }
    }

    queueLenChanges() {
        this.sumOfQueueLenghts += (this.d.time - this.timeOfQueueChanges) * this.queue
        this.timeOfQueueChanges = this.d.time
        // console.log()
    }

    cpuLoad(timeToComplete) {
        if (this.d.time + timeToComplete < this.d.timeLimit)
            this.cpuLoadTime += timeToComplete
        else
            this.cpuLoadTime += this.d.timeLimit - this.d.time
    }

    avgCPUload() {
        return this.cpuLoadTime / this.d.timeLimit / this.numOfCores * 100
    }

    calcAvgQueueLen() {
        this.queueLenChanges()
        return this.sumOfQueueLenghts / this.d.timeLimit
    }

    calcFailureProbability() {
        const created = this.created === 0 ? 1 : this.created
        return this.failed / created * 100
    }
}
