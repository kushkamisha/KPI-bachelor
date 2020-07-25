'use strict'

const expect = require('chai').expect
const Processor = require('../Processor')
const { getNextNotCompletelyBusyByPriority } = require('../utils')


const sharedData = {
    time: 0,
    timeLimit: 10,
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
const processors = [
    {
        name: '#1',
        pr: new Processor(sharedData, processorParams, '#1'),
        next: ['#2', '#3', '#4'],
        nextPriority: [0, 3, 2]
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
]

describe.skip(`Checks 'getNextNotCompletelyBusyByPriority' function`, () => {
    it('should return the index of the next processor selected by priority', () => {
        expect(getNextNotCompletelyBusyByPriority('#1', processors)).equal(1)
    })

    it.skip('should return the index of the next not copletely busy processor selected by priority', () => {
        processors[2].queue = 5
        expect(getNextNotCompletelyBusyByPriority('#1', processors)).equal(11)
    })
})
