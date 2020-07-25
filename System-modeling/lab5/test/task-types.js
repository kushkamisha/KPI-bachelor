'use strict'

const expect = require('chai').expect
const Processor = require('../Processor')
const Simulator = require('../Simulator')


const sharedData = {
    time: 0,
    timeLimit: 1000000,
    taskCreationTime: {},
    taskCompletionTimes: {}
}
const simulatorParams = {
    processors: [
        {
            name: 'Admissions Office',
            pr: new Processor(sharedData, {
                queueLimit: Infinity,
                numOfCores: 2,
                timeAvgToCreate: 15,
                types: {
                    appearProbs: [0.5, 0.1, 0.4],
                    timesAvgToComplete: [15, 40, 30]
                },
                showLogs: false
            }, 'Admissions Office')
        }
    ],
    showLogs: false
}

describe('Test the model with tasks of different types', () => {
    let simulator, pr

    before(() => {
        simulator = new Simulator(sharedData, simulatorParams);
        [pr] = simulator.start()
    })

    it('created tasks of types #0 / #1 should correlate as 5 to 1', () => {
        expect(pr.created[0] / pr.created[1]).to.be.within(4.7, 5.3)
    })
    it('created tasks of types #1 / #2 should correlate as 1 to 4', () => {
        expect(pr.created[2] / pr.created[1]).to.be.within(3.5, 4.5)
    })
})
