'use strict';
const util = require('node:util');
const os = require('os');
// Printing os.platform() value
var platform = os.platform();
let Example = undefined;
switch(platform) {
    case 'linux': 
    console.log("Linux Platform");
    Example = require('./lib/occt');
        break;
    case 'win32': 
    console.log("windows platform");
    Example = require('./bin/occt');
        break;    
    default: console.log("unknown platform");
}

const pt1 = new Example.Pnt2d(11,12);
const dir = new Example.Pnt2d(13,14);
//console.log(JSON.stringify(example));
console.log(util.inspect(pt1, { showHidden: true,getters: true }));

const line = new Example.Line2d(pt1, dir);
//console.log(JSON.stringify(example));
console.log(util.inspect(line, { showHidden: true,getters: true }));

