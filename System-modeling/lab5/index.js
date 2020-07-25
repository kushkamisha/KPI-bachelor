'use strict'

const ModelCreator = require('./ModelCreator')


const sharedData = {
    time: 0,
    timeLimit: 10,
    taskCreationTime: {},
    taskCompletionTimes: {}
}
const processorParams = {
    queueLimit: 3,
    numOfCores: 2,
    timeAvgToCreate: 1,
    timeAvgToComplete: 0.7,
    showLogs: true
}

const params = {
    numOfProcessors: 8,
    sharedData,
    processorParams,
    showLogs: true,
    structure: 'tree'
}
const creator = new ModelCreator(params)
creator.start()
