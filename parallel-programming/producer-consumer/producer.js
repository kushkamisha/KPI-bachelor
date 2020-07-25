'use strict'

const threads = require('worker_threads')
const { parentPort } = threads

let port
const { buffer } = threads.workerData
const arr = new Int8Array(buffer)

function loop(i) {
    if (i === 0) {
        port.postMessage('done')
        process.exit(0)
    }
    
    const val = Math.floor(Math.random() * 128)
    arr[arr.indexOf(0)] = val
    console.log(`\x1b[33mProducer: ${val}\x1b[0m`)
    port.postMessage('add')

    setTimeout(() => loop(i - 1), 100)
}

parentPort.on('message', data => {
    if (data.type === 'port') {
        port = data.port
        loop(5)
    }
})
