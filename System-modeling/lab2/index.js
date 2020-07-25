'use strict'

const Model = require('./model')


const modelParams = {
    tmAvgToCreate: 1,
    tmAvgToComplete: 1,
    maxQueueLen: 5,
    currentTime: 0,
    iIsBusy: false,
    iAppearTime: 0,
    iCompleteTime: 0
}

const model = new Model(modelParams)
model.simulate({ maxExecTime: 5 })
