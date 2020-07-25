'use strict'

const child_process = require('child_process')
const { rand } = require('./utils')

const N = 1000000
const arr1 = new Array(N).fill().map(_ => rand(0, 100))
const arr2 = new Array(N).fill().map(_ => rand(0, 100))

const sumOfArraySync = arr => arr.reduce((a, b) => a + b)

const sumOfArray = arr => new Promise(resolve => {
    const cores = require('os').cpus().length
    let done = 0
    let sum = 0
    for (let i = 0; i < cores; i++) {
        const child = child_process.fork('./child-sum')

        child.send({
            arr,
            start: Math.floor(N / cores * i),
            end: i === cores - 1 ? N : Math.floor(N / cores * (i + 1))
        })

        child.on('message', msg => {
            // console.log('[parent] received message from child:', msg)
            sum += msg.sum
            done++
            if (done === cores) resolve(sum)
        })
    }
})

const filterArr = (arr, val, option='more') => new Promise(resolve => {
    const cores = require('os').cpus().length
    let done = 0
    let res = []
    for (let i = 0; i < cores; i++) {
        const child = child_process.fork(option === 'more' ?
            './child-filter-more': './child-filter-less')

        child.send({
            arr,
            val,
            start: Math.floor(N / cores * i),
            end: i === cores - 1 ? N : Math.floor(N / cores * (i + 1))
        })

        child.on('message', msg => {
            // console.log('[parent] received message from child:', msg)
            res = res.concat(msg.res)
            done++
            if (done === cores) resolve(res)
        })
    }
})

const avg1 = sumOfArraySync(arr1) / N
const avg2 = sumOfArraySync(arr2) / N
console.log({ avg1, avg2 })

// Syncronous
// console.time('Sync code')
const res = [
    ...arr2.filter(x => x < avg2).sort((a, b) => a - b),
    ...arr1.filter(x => x > avg1).sort((a, b) => a - b)
]
// console.timeEnd('Sync code')
console.dir({ res })

// Asyncronous
// console.time('Async code')
Promise.all([ sumOfArray(arr1), sumOfArray(arr2) ])
    .then(([sum1, sum2]) => {
        const avg1 = sum1 / N
        const avg2 = sum2 / N
        console.log({ avg1, avg2 })
        return Promise.all([
            filterArr(arr1, avg1), filterArr(arr2, avg2, 'less')
        ])
    })
    .then(([res1, res2]) => {
        const res = res1.concat(res2).sort((a, b) => a - b)
        // console.timeEnd('Async code')
        console.dir({ res })
        process.exit(0)
    })
