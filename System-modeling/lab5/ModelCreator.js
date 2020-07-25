'use strict'

const Simulator = require('./Simulator')
const Processor = require('./Processor')
const { getPrevProcessorIndex } = require('./utils')


module.exports = class ModelCreator {

    constructor(params) {
        this.sharedData = params.sharedData
        this.processorParams = params.processorParams
        this.simulatorParams = { processors: [], showLogs: params.showLogs }
        this.numOfProcessors = params.numOfProcessors
        this.maxNumOfEvents = this.numOfProcessors + 1
        this.structure = params.structure
    }

    getNextProcessor(i, max) {
        let next = []
        
        switch(this.structure) {
            case 'linear':
                next = i !== max - 1 ? [`#${i + 1}`] : []
                break
            case 'tree':
                next = []
                // eslint-disable-next-line no-case-declarations
                const prevIndex = getPrevProcessorIndex(i)
                if (prevIndex !== -1)
                    this.simulatorParams.processors[prevIndex].next.push(`#${i}`)
                break
        }

        return next
    }

    createProcessors() {
        const max = this.numOfProcessors
        for (let i = 0; i < max; i++) {
            this.simulatorParams.processors.push({
                name: `#${i}`,
                pr: new Processor(this.sharedData, {
                    queueLimit: 3,
                    numOfCores: 2,
                    timeAvgToCreate: 1,
                    timeAvgToComplete: 0.7,
                    showLogs: this.simulatorParams.showLogs
                }, `#${i}`),
                next: this.getNextProcessor(i, max),
                nextProb: this.structure === 'tree' ? [0.5, 0.5] : [1]
            })
        }
    }

    start() {
        this.createProcessors()
        const simulator = new Simulator(
            this.sharedData, this.simulatorParams, this.maxNumOfEvents)
        simulator.start()
    }
}
