'use strict'

const { Worker, MessageChannel } = require('worker_threads')
const { port1, port2 } = new MessageChannel()

const buffer = new SharedArrayBuffer(10)

const consumer = new Worker('./consumer.js', { workerData: { buffer } })
const producer = new Worker('./producer.js', { workerData: { buffer } })

consumer.postMessage({ type: 'port', port: port2 }, [port2])
producer.postMessage({ type: 'port', port: port1 }, [port1])
