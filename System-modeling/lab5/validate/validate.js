'use strict'

const ModelCreator = require('../ModelCreator')
const { round } = require('../utils')
let { sharedData, processorParams } = require('./data')


const sharedDataOriginal = { ...sharedData }
const processorParamsOriginal = { ...processorParams }

const restoreData = () => {
    sharedData = { ...sharedDataOriginal }
    processorParams = { ...processorParamsOriginal }
}

const numOfEvents = [5, 10, 15, 25, 40, 65, 105, 170]

// Validation process
const resultsLinear = []
const resultsTree = []

for (let i = 0; i < 2; i++) {
    numOfEvents.forEach(eventsLimit => {
        restoreData()

        const params = {
            numOfProcessors: eventsLimit,
            sharedData,
            processorParams,
            showLogs: false,
            structure: i === 0 ? 'linear' : 'tree'
        }
        const creator = new ModelCreator(params)
        creator.start()

        const results = { 'Events limit': eventsLimit, 'Working time (s)': round(sharedData.time) }
        if (i === 0)
            resultsLinear.push(results)
        else
            resultsTree.push(results)
    })
}

console.log('\nLinear')
console.table(resultsLinear)
console.log('\nTree')
console.table(resultsTree)
