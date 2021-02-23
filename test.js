const smemory = require('./index');
console.log('Init Share Memory=>', smemory);


let ret = smemory.CreateShareMemory('my-addon-test-memory', 64);
console.log('CreateShareMemory=>', ret);

let writebuff = new ArrayBuffer(10);
let u8arr = new Uint8Array(writebuff);
u8arr[0] = 9;
u8arr[1] = 7;
u8arr[2] = 5;
u8arr[3] = 3;
u8arr[4] = 1;
ret = smemory.WriteShareMemory('my-addon-test-memory', writebuff);
console.log('WriteShareMemory=>', ret);

let readbuff = new ArrayBuffer(10);
ret = smemory.ReadShareMemory('my-addon-test-memory', readbuff);
console.log('ReadShareMemory=> ', ret, new Uint8Array(readbuff));

ret = smemory.DeleteShareMemory('my-addon-test-memory');
console.log('DeleteShareMemory=> ', ret);

readbuff = new ArrayBuffer(10);
ret = smemory.ReadShareMemory('my-addon-test-memory', readbuff);
console.log('ReadShareMemory=> ', ret, new Uint8Array(readbuff));