# share-memory-win
a share memory module between diffrent process on windows. runtime nodejs/electron.

## example
```js
const smemory = require('share-memory-win');
console.log('Init Share Memory=>', smemory);

let ret = smemory.CreateShareMemory('my-addon-test-memory', 64);
console.log('CreateShareMemory=>', ret);
//CreateShareMemory=> true


let writebuff = new ArrayBuffer(10);
let u8arr = new Uint8Array(writebuff);
u8arr[0] = 9;
u8arr[1] = 7;
u8arr[2] = 5;
u8arr[3] = 3;
u8arr[4] = 1;
ret = smemory.WriteShareMemory('my-addon-test-memory', writebuff);
console.log('WriteShareMemory=>', ret);
//WriteShareMemory=> true


let readbuff = new ArrayBuffer(10);
ret = smemory.ReadShareMemory('my-addon-test-memory', readbuff);
console.log('ReadShareMemory=> ', ret, new Uint8Array(readbuff));
//ReadShareMemory=>  true Uint8Array [ 9, 7, 5, 3, 1, 0, 0, 0, 0, 0 ]


ret = smemory.DeleteShareMemory('my-addon-test-memory');
console.log('DeleteShareMemory=> ', ret);
//DeleteShareMemory=>  true


readbuff = new ArrayBuffer(10);
ret = smemory.ReadShareMemory('my-addon-test-memory', readbuff);
console.log('ReadShareMemory=> ', ret, new Uint8Array(readbuff));
//ReadShareMemory=>  false Uint8Array [ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ]
```

## install
### nodejs
```bash
npm i share-memory-win
```
### electron
```
npm install --save-dev electron-rebuild
npm install --save-dev electron-prebuilt
.\node_modules\.bin\electron-rebuild.cmd -v 10.1.5/your electron version -w share-memory-win
```
