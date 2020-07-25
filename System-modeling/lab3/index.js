'use strict'

const Simulator = require('./Simulator')
const Processor = require('./Processor')

const sharedData = {
    time: 0,
    timeLimit: 5,
    taskCreationTime: { },
    taskCompletionTimes: { }
}
const processorParams = {
    queueLimit: 5,
    numOfCores: 2,
    timeAvgToCreate: 1,
    timeAvgToComplete: 1,
    showLogs: true
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
            nextProb: [1]
        },
        {
            name: '#4',
            pr: new Processor(sharedData, processorParams, '#4'),
            next: ['#1'],
            nextProb: [0.3]
        }
    ],
    showLogs: true
}

const simulator = new Simulator(sharedData, simulatorParams)
simulator.start()
