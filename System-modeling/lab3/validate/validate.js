'use strict'

const Simulator = require('../Simulator')
const Processor = require('../Processor')
let { sharedData, processorParams } = require('./data')

const sharedDataOriginal = { ...sharedData }
const processorParamsOriginal = { ...processorParams }

const restoreData = () => {
    sharedData = { ...sharedDataOriginal }
    processorParams = { ...processorParamsOriginal }
}

const recreateProcessors = () =>
    simulatorParams.processors.map(x => x.pr = new Processor(sharedData, processorParams, x.name))

let simulatorParams = {
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
    showLogs: false
}

const validationChanges = [
    () => {},
    () => sharedData.timeLimit = 2,
    () => processorParams.queueLimit = 100,
    () => processorParams.numOfCores = 64,
    () => processorParams.timeAvgToCreate = 5
]

// Validation process
validationChanges.forEach(change => {
    restoreData()
    change()
    recreateProcessors()

    const simulator = new Simulator(sharedData, simulatorParams)
    const res = simulator.start()

    console.table([{ ...sharedData, ...processorParams }])
    console.table(res)
})
