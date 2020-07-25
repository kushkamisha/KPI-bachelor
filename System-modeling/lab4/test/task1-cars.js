'use strict'

const expect = require('chai').expect
const Processor = require('../Processor')
const Simulator = require('../Simulator')


const sharedData = {
    time: 0,
    initialTime: 0.1,
    timeLimit: 100000,
    taskCreationTime: {},
    taskCompletionTimes: {}
}
const processorParams = {
    queueLimit: 3,
    numOfCores: 1,
    timeAvgToComplete: 0.3,
    initialQlen: 2,
    showLogs: false
}
const simulatorParams = {
    processors: [
        {
            name: 'entrance',
            pr: new Processor(sharedData, {
                queueLimit: Infinity,
                numOfCores: Infinity,
                timeAvgToCreate: 0.5,
                timeAvgToComplete: 0,
                showLogs: false
            }, 'entrance'),
            next: ['#1', '#2']
        },
        {
            name: '#1',
            pr: new Processor(sharedData, processorParams, '#1'),
            priority: 1
        },
        {
            name: '#2',
            pr: new Processor(sharedData, processorParams, '#2'),
            priority: 0
        }
    ],
    showLogs: false,
    is4CarsTask: true
}

describe('Test the task 1 - cars in a bank', () => {
    let simulator, pr1, pr2

    before(() => {
        simulator = new Simulator(sharedData, simulatorParams);
        [, pr1, pr2] = simulator.start()
    })

    it('cpu load for #1 should be close enough to the given one', () => {
        expect(pr1.avgCPUload).to.be.within(49.0, 49.4)
    })
    it('cpu load for #2 should be close enough to the given one', () => {
        expect(pr2.avgCPUload).to.be.within(10.5, 11)
    })

    it('number of queue changes', () => {
        expect(pr1.queueChanges).to.be.within(1400, 1600)
    })

    it('average visit time #1', () => {
        expect(pr1.avgVisitTime).to.be.within(0.40, 0.42)
    })
    it('average visit time #2', () => {
        expect(pr2.avgVisitTime).to.be.within(0.3, 0.4)
    })
})
