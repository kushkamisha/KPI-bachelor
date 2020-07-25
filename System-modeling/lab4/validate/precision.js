'use strict'

const Simulator = require('../Simulator')
const Processor = require('../Processor')

const sharedData = {
    time: 0,
    timeLimit: 3000000,
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
            nextProb: [0.15, 0.13, 0.3],
            // nextPriority: [1, 0]
        },
        {
            name: '#2',
            pr: new Processor(sharedData, {
                queueLimit: 999,
                numOfCores: 1,
                timeAvgToCreate: 2,
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
                timeAvgToCreate: 2,
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
                timeAvgToCreate: 2,
                timeAvgToComplete: 0.1,
                showLogs: false
            }, '#4'),
            next: ['#1'],
            nextProb: [1]
        }
    ],
    showLogs: true
}

const simulator = new Simulator(sharedData, simulatorParams)
simulator.start()
