'use strict'

const { erlang } = require('./distributions')
const random = require('random')


/**
 * Generates a random value according to an exponential distribution
 */
const randomExp = (timeMean = 5) => {
    let num = 0
    while (num === 0) num = Math.random()
    return -timeMean * Math.log(num)
}

const randomErlang = (alpha, beta) => erlang(alpha, beta)

const randomUniform = (min, max) => random.uniform(min, max)()

/**
 * Round a number to <precision> digits
 */
const round = (num, precision = 3) => {
    return Math.round(num * 10 ** precision) / 10 ** precision
}

/**
 * Gets an index of the element by <probs>. If <probs> is an empty array -
 * generate equal probabilities using the <numOfElements>.
 */
const getRandomWithProbability = (probs, numOfElems) => {
    // If probs is undefined - generate equal probabilities using the number
    // of elements
    if (!probs)
        probs = new Array(numOfElems).fill(1 / numOfElems)

    // If probs is an empty array - push 1 into it 
    if (!probs.length)
        probs = [1]

    // If sum of probabilities is less than 1 - add new item, so that now
    // the sum would be 1
    const sumOfProbs = probs.reduce((acc, x) => acc += x)
    if (sumOfProbs < 1)
        probs.push(1 - sumOfProbs)

    const num = Math.random()
    let s = 0
    const lastIndex = probs.length - 1

    for (let i = 0; i < lastIndex; ++i) {
        s += probs[i]
        if (num < s) {
            return i
        }
    }

    return lastIndex
}

const selectNextByPriority = (nextNames, processorsData) => {
    let nextPrsData = processorsData.filter(x => nextNames.includes(x.pr.name))
    // Select Qs from the next lst with the smallest current Q length
    const qs = []
    nextPrsData.forEach(x => qs.push(x.pr.queue.length))

    let maxPriority = -1
    let index = -1
    nextPrsData.forEach((x, i) => {
        if (x.pr.queue.length === Math.min(...qs) && x.priority > maxPriority) {
            maxPriority = x.priority
            index = i
        }
    })

    return index
}

const getPrevProcessorIndex = index => {
    let treeLvl = 0
    let counter = 0
    while (index > counter) {
        ++treeLvl
        counter += 2 ** treeLvl
    }
    const lvlWidth = 2 ** treeLvl

    const prvLvlLastIndex = counter - lvlWidth
    let parent = prvLvlLastIndex
    let flag = false
    while (counter > prvLvlLastIndex) {
        if (counter === index) break
        --counter
        if (flag) --parent
        flag = !flag
    }

    return parent
}

const sum = arr => arr.reduce((acc, x) => acc += x, 0)

const average = arr => sum(arr) / arr.length

module.exports = {
    random: {
        exp: randomExp,
        uniform: randomUniform,
        erlang: randomErlang
    },
    round,
    getRandomWithProbability,
    selectNextByPriority,
    getPrevProcessorIndex,
    sum,
    average
}
