'use strict'

const expect = require('chai').expect

const Simulator = require('../Simulator')
const Processor = require('../Processor')

const sharedData = {
    time: 0,
    timeLimit: 10000,
    taskCreationTime: {},
    taskCompletionTimes: {}
}
const processorParams = {
    queueLimit: 5,
    numOfCores: 2,
    timeAvgToCreate: 1,
    timeAvgToComplete: 1,
    showLogs: false
}

const simulatorParams = {
    processors: [
        {
            name: '#1',
            pr: new Processor(sharedData, processorParams, '#1'),
            next: ['#2', '#3'],
            nextProb: [0.3, 0.7]
        },
        {
            name: '#2',
            pr: new Processor(sharedData, processorParams, '#2'),
        },
        {
            name: '#3',
            pr: new Processor(sharedData, processorParams, '#3'),
            next: ['#4'],
            nextProb: []
        },
        {
            name: '#4',
            pr: new Processor(sharedData, processorParams, '#4'),
            next: ['#1'],
            nextProb: [0.3]
        }
    ],
    showLogs: false
}

describe('Test the whole simulator model with set probabilities', () => {
    let simulator, pr2, pr3, pr4

    before(() => {
        simulator = new Simulator(sharedData, simulatorParams);
        [, pr2, pr3, pr4] = simulator.start()
    })

    it('the num of compl tasks in #3 should be equal to the num of created in #4', () => {
        expect(pr3.completed[0]).equal(pr4.created[0])
    })

    it('the num of created in #2 should be about 2.3 times less than in #3', () => {
        expect(pr3.created[0] / pr2.created[0]).to.be.within(2.1, 2.5)
    })
})
