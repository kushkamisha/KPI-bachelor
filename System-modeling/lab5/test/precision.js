'use strict'

const expect = require('chai').expect

const Simulator = require('../Simulator')
const Processor = require('../Processor')

const sharedData = {
    time: 0,
    timeLimit: 1000000,
    taskCreationTime: {},
    taskCompletionTimes: {}
}
const simulatorParams = {
    processors: [
        {
            name: '#1',
            pr: new Processor(sharedData, {
                queueLimit: 999,
                numOfCores: 1,
                timeAvgToCreate: 2,
                timeAvgToComplete: 0.6,
                showLogs: false
            }, '#1'),
            next: ['#2', '#3', '#4'],
            nextProb: [0.15, 0.13, 0.3]
        },
        {
            name: '#2',
            pr: new Processor(sharedData, {
                queueLimit: 999,
                numOfCores: 1,
                timeAvgToComplete: 0.3,
                showLogs: false
            }, '#2'),
            next: ['#1'],
            nextProb: [1]
        },
        {
            name: '#3',
            pr: new Processor(sharedData, {
                queueLimit: 999,
                numOfCores: 1,
                timeAvgToComplete: 0.4,
                showLogs: false
            }, '#3'),
            next: ['#1'],
            nextProb: [1]
        },
        {
            name: '#4',
            pr: new Processor(sharedData, {
                queueLimit: 999,
                numOfCores: 2,
                timeAvgToComplete: 0.1,
                showLogs: false
            }, '#4'),
            next: ['#1'],
            nextProb: [1]
        }
    ],
    showLogs: false
}

describe('Test the whole simulation for the lecture.png model', () => {
    let simulator, pr1, pr2, pr3, pr4

    before(() => {
        simulator = new Simulator(sharedData, simulatorParams);
        [pr1, pr2, pr3, pr4] = simulator.start()
    })

    it('cpu load for #1 should be close enough to the given one', () => {
        expect(pr1.avgCPUload).to.be.within(71.4 - 0.5, 71.4 + 0.5)
    })
    it('cpu load for #2 should be close enough to the given one', () => {
        expect(pr2.avgCPUload).to.be.within(5.2, 5.6)
    })
    it('cpu load for #3 should be close enough to the given one', () => {
        expect(pr3.avgCPUload).to.be.within(6.0, 6.4)
    })
    it('cpu load for #4 should be close enough to the given one', () => {
        expect(pr4.avgCPUload).to.be.within(1.6, 2.0)
    })

    it('queue avg length for #1 should be close enough to the given one', () => {
        expect(pr1.avgQueueLen).to.be.within(1.786 - 0.1, 1.786 + 0.1)
    })
    it('queue avg length for #2 should be close enough to the given one', () => {
        expect(pr2.avgQueueLen).to.be.within(0.003 - 0.0005, 0.003 + 0.0005)
    })
    it('queue avg length for #3 should be close enough to the given one', () => {
        expect(pr3.avgQueueLen).to.be.within(0.004 - 0.0005, 0.004 + 0.0005)
    })
    it('queue avg length for #4 should be close enough to the given one', () => {
        expect(pr4.avgQueueLen).to.be.within(0.00001 - 0.000005, 0.00001 + 0.000005)
    })
})
