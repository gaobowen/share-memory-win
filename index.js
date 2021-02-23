
if (process.platform !== 'win32') {
    throw new Error('Only works on windows.')
} else {
    const addon = require('bindings')('share_memory_win')
    module.exports = addon
}