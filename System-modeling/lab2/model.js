'use strict'

const { randomExp, round } = require('./utils')


module.exports = class Model {

    constructor({
        tmAvgToCreate,
        tmAvgToComplete,
        maxQueueLen,
        currentTime,
        iIsBusy, // i - initial
        iAppearTime,
        iCompleteTime,
        showLog=true
    }) {
        this.timeAvgToCreate = tmAvgToCreate
        this.tmAvgToComplete = tmAvgToComplete
        this.maxQueueLen = maxQueueLen
        this.initialTime = this.time = currentTime
        this.isBusy = iIsBusy
        this.timeOfCreation = currentTime + iAppearTime
        this.timeOfCompletion = currentTime + iCompleteTime
        this.showLog = showLog

        this.queueLen =
        this.numCompleted =
        this.numCreated =
        this.numFailed =
        this.sumOfRangesLoad =
        this.startToWorkTime =
        this.endToWorkTime =
        this.sumOfWaitInQueueTime =
        this.numsWereInQueue = 0

        this.timeOfPutInQueue = []

        this.events = Object.freeze({
            'create': 0,
            'completed': 1
        })
        this.eventType = this.events.create
    }

    simulate({ maxExecTime }) {
        // for an Avg device load calculation
        this.maxExecTime = maxExecTime

        while (this.time < maxExecTime) {

            [this.time, this.eventType] =
                this.timeOfCompletion < this.timeOfCreation ?
                    [this.timeOfCompletion, this.events.completed] :
                    [this.timeOfCreation, this.events.create]

            if (this.eventType === this.events.create)
                this.eventCreate()
            else if (this.eventType === this.events.completed)
                this.eventCompleted()

            this.printStepInfo()

        }
        this.printOverallInfo()

        return {
            created:   this.numCreated,
            completed: this.numCompleted,
            failed:    this.numFailed,
            queue:     this.queueLen,
            isBusy:    this.isBusy,
            avgLoad:   round(this.getAvgDeviceLoad(), 3),
            avgWait:   round(this.getAvgWaitTime(), 3)
        }
    }

    eventCreate() {
        // If we try to create after ending of execution time - don't count it
        if (this.timeOfCreation <= this.maxExecTime)
            this.numCreated++

        // If initial state is busy - don't count completion of it
        if (this.iIsBusy) this.numCreated--

        const timeToCreate = this.getTimeToCreate()
        this.timeOfCreation = this.time + timeToCreate

        // Start to process or put in the queue
        if (!this.isBusy) {
            this.isBusy = true
            const timeToComplete = this.getTimeToComplete()
            this.timeOfCompletion = this.time + timeToComplete
            this.sumUpRangesLoad(timeToComplete)
        } else {
            if (this.queueLen < this.maxQueueLen) {
                this.queueLen++
                // remember time when push in the queue
                this.timeOfPutInQueue.push(this.time)
            } else this.numFailed++
        }
    }

    eventCompleted() {
        this.timeOfCompletion = Infinity
        this.numCompleted++
        this.isBusy = false

        // Get an element from the queue if it's not empty
        if (this.queueLen > 0) {
            this.queueLen--
            this.sumOfWaitInQueueTime +=
                this.time - this.timeOfPutInQueue.shift()
            this.numsWereInQueue += 1

            this.isBusy = true
            const timeToComplete = this.getTimeToComplete()
            this.timeOfCompletion = this.time + timeToComplete
            this.sumUpRangesLoad(timeToComplete)
        }
    }

    getTimeToCreate() {
        return randomExp(this.timeAvgToCreate)
    }

    getTimeToComplete() {
        return randomExp(this.tmAvgToComplete)
    }

    sumUpRangesLoad(timeToComplete) {
        // console.log({ timeToComplete })
        // console.log(`Time of completion = ${this.timeOfCompletion}`)
        if (this.time < this.maxExecTime) {
            if (this.timeOfCompletion <= this.maxExecTime)
                this.sumOfRangesLoad += timeToComplete
            else
                this.sumOfRangesLoad += (this.maxExecTime - this.time)
        }
    }

    getAvgDeviceLoad() {
        return this.sumOfRangesLoad / (this.maxExecTime - this.initialTime)
    }

    getAvgWaitTime() {
        // Count all tasks created before the end of time, but which weren't
        // completed
        while (this.timeOfPutInQueue.length) {
            const taskTime = this.timeOfPutInQueue.shift()
            if (taskTime <= this.maxExecTime) {
                this.numsWereInQueue++
                this.sumOfWaitInQueueTime += this.maxExecTime - taskTime
            }
        }

        if (this.numsWereInQueue === 0) return 0

        return this.sumOfWaitInQueueTime / this.numsWereInQueue
    }

    printStepInfo() {
        if (!this.showLog) return false
        console.log(`
            Time:           ${round(this.time, 3)}
            Is busy:        ${this.isBusy}
            Queue length:   ${this.queueLen}
            Type:           ${this.eventType === 0 ? 'create' : 'completed'}`)
    }

    printOverallInfo() {
        if (!this.showLog) return false
        console.log(`
            =================================
            \x1b[36mCreated:        ${this.numCreated}\x1b[0m
            \x1b[32mCompleted:      ${this.numCompleted}\x1b[0m
            \x1b[31mFailed:         ${this.numFailed}\x1b[0m

            \x1b[33mAvg load:       ${round(this.getAvgDeviceLoad(), 3)}
            Avg wait time:  ${round(this.getAvgWaitTime(), 3)}\x1b[0m
            `)
    }

}
