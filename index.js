const Lc = require('bindings')('lc')

console.log(Lc.hello());
console.log(Lc.fuck());
console.log(Lc.word);

const net = require('net')