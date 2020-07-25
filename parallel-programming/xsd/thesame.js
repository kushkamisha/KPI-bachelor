'use strict'

const fs = require('fs')
const parser = require('xml2json')

const xml = fs.readFileSync('paper.xml', 'utf8')

// xml to json
const rawJson = parser.toJson(xml)
const papers = JSON.parse(rawJson).Catalog.Paper
// console.dir(papers)

papers.sort((a, b) => a.Title > b.Title ? 1 : -1)
console.dir(papers)
