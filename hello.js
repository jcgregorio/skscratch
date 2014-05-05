n = require('./skia/gyp/build/Release/hello.node');
console.log(n.draw());
fs = require('fs');

fs.writeFileSync('file.txt', 'Hello World!');

