'use strict'

const threads = require('worker_threads')
const { parentPort } = threads
const { buffer } = threads.workerData

let port
let isProducerDone = false
const arr = new Int8Array(buffer)

parentPort.on('message', data => {
    if (data.type === 'port') {
        port = data.port

        port.on('message', msg => {
            if (msg === 'add') {
                setTimeout(() => {
                    const indexOfZero = arr.indexOf(0)
                    if (indexOfZero !== 0) {
                        const index = indexOfZero === -1 ?
                            arr.length - 1 : indexOfZero - 1
                        console.log(`\x1b[36mConsumer: ${arr[index]}\x1b[0m`)
                        arr[index] = 0
                    }

                    if (arr.filter(x => x === 0).length === arr.length &&
                            isProducerDone) process.exit(0)
                }, 300)
            }

            if (msg === 'done') {
                console.log('producer: done')
                isProducerDone = true

                if (arr.filter(x => x === 0).length === arr.length) {
                    console.log('arr is empty')
                    process.exit(0)
                }
            }
        })
    }
})
