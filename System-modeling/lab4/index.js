'use strict'

const Simulator = require('./Simulator')
const Processor = require('./Processor')

const sharedData = {
    time: 0,
    timeLimit: 300,
    taskCreationTime: {},
    taskCompletionTimes: {}
}

const names = {
    admissionsOffice: '🏥  Admissions Office',
    ward: '🛏  ward',
    walking2lab: '🚶  walking 2 lab',
    labReception: '🛎  lab reception',
    labAssistance: '💉  lab assistance',
    walking2office: '🚶  walking 2 office'
}

const simulatorParams = {
    processors: [
        {
            name: names.admissionsOffice,
            pr: new Processor(sharedData, {
                queueLimit: Infinity,
                numOfCores: 2,
                timeAvgToCreate: 15,
                types: {
                    appearProbs: [0.5, 0.1, 0.4],
                    timesAvgToComplete: [15, 40, 30]
                },
                showLogs: true
            }, names.admissionsOffice),
            next: [names.ward, names.walking2lab, names.walking2lab],
            nextByTypes: [0, 1, 2]
        },
        {
            name: names.ward,
            pr: new Processor(sharedData, {
                queueLimit: Infinity,
                numOfCores: 3,
                timeAvgToComplete: [3, 8],
                distribution: 'uniform',
                showLogs: true
            }, names.ward),
        },
        {
            name: names.walking2lab,
            pr: new Processor(sharedData, {
                queueLimit: Infinity,
                numOfCores: Infinity,
                timeAvgToComplete: [2, 5],
                distribution: 'uniform',
                showLogs: true
            }, names.walking2lab),
            next: [names.labReception],
            nextProb: [1]
        },
        {
            name: names.labReception,
            pr: new Processor(sharedData, {
                queueLimit: Infinity,
                numOfCores: 1,
                timeAvgToComplete: [4.5, 3],
                distribution: 'erlang',
                showLogs: true
            }, names.labReception),
            next: [names.labAssistance],
            nextProb: [1]
        },
        {
            name: names.labAssistance,
            pr: new Processor(sharedData, {
                queueLimit: Infinity,
                numOfCores: 2,
                timeAvgToComplete: [4, 2],
                distribution: 'erlang',
                showLogs: true
            }, names.labAssistance),
            next: [names.walking2office],
            nextProb: [0.5]
        },
        {
            name: names.walking2office,
            pr: new Processor(sharedData, {
                queueLimit: Infinity,
                numOfCores: Infinity,
                timeAvgToComplete: [2, 5],
                distribution: 'uniform',
                showLogs: true
            }, names.walking2office),
            next: [names.admissionsOffice],
            nextProb: [1]
        }
    ],
    showLogs: true
}

const simulator = new Simulator(sharedData, simulatorParams)
simulator.start()
