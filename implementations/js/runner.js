if (typeof performance === 'undefined') {
  var performance = Date
}

var twister = require('./twister/ostrich-twister-prng.js')
var ndarray = require('ndarray')
var ops = require('ndarray-ops')
var show = require('ndarray-show')

function rand(size1, size2) {
  if (size1 === 'undefined') {
    return twister.random()
  }

  if (size2 === undefined) {
    size2 = size1
  }

  var array = ndarray(new Float64Array(size1 * size2), [size1, size2])

  for (var i = 0; i < size1; ++i) {
    for (var j = 0; j < size2; ++j) {
      array.set(j, i, twister.random())
    }
  }

  return array
}

function runner (size) {
  twister.seed(1337)
  var input = rand(size, size)
  ops.mulseq(input,10000)
  ops.flooreq(input)

  //console.log(show(input))
  //console.log()

  var output = input.data.slice()

  var t1 = performance.now()
  lud(output, size)
  var t2 = performance.now()

  output = ndarray(output, [size, size])
  ops.mulseq(output, 100)
  ops.flooreq(output)

  //console.log(show(output))

  var checksum = fletcher_sum_ndarray(output)

  console.log(JSON.stringify({
    status: 1,
    options: 'run(' + size + ')',
    time: (t2 - t1) / 1000,
    output: checksum
  }))
}
