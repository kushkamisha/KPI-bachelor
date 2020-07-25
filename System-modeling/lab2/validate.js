'use strict'

const Model = require('./model')


const maxExecTime = 1000
const modelParams = {
    tmAvgToCreate: 1,
    tmAvgToComplete: 2,
    maxQueueLen: 5,
    currentTime: 0,
    iIsBusy: false,
    iAppearTime: 0,
    showLog: false,
    iCompleteTime: 0,
    maxExecTime,
    "😎": "😎"
}

const results = []
const recreateModel = (modelParams, results, maxExecTime=1000) => {
    const model = new Model(modelParams)

    delete modelParams.showLog
    delete modelParams.iAppearTime
    delete modelParams.iCompleteTime

    results.push({ ...modelParams, ...model.simulate({ maxExecTime }) })

    modelParams.showLog = false
    modelParams.iAppearTime =
    modelParams.iCompleteTime = 0
}

recreateModel(modelParams, results)

modelParams.tmAvgToComplete = 10
recreateModel(modelParams, results)
modelParams.tmAvgToComplete = 2

modelParams.tmAvgToCreate = 6
recreateModel(modelParams, results)
modelParams.tmAvgToCreate = 1

modelParams.maxQueueLen = 1000
recreateModel(modelParams, results)
modelParams.maxQueueLen = 5

modelParams.currentTime = 500
recreateModel(modelParams, results)
modelParams.currentTime = 0

modelParams.maxExecTime = 5
recreateModel(modelParams, results, modelParams.maxExecTime)

modelParams.iIsBusy = true
modelParams.maxExecTime = 5
recreateModel(modelParams, results, modelParams.maxExecTime)
modelParams.iIsBusy = false

console.table(results)
