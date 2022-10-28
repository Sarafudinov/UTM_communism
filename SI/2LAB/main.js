//------------------------------- Parameter Generation -------------------------------

const min = 0;
const max = 1000;

let randMin = Math.round(Math.random() * (max - min) + min);
let randMax = Math.round(Math.random() * (max - min) + min);

while (randMax <= randMin) {
    randMin = Math.round(Math.random() * (max - min) + min);
    randMax = Math.round(Math.random() * (max - min) + min);
}

let hash = 0;
let q = 0;
let p = 0;

console.log(`The get number between ${randMin} and ${randMax} are:`);

hash = Math.round(Math.random() * (randMax - randMin) + randMin);
q = getPrimeNumber();
p = (q-1)/2

console.log(`\nhash = ${hash}`);
console.log(`\npars hash = ${hash.toString(2)}`);
console.log(`hash len = ${hash.toString(2).length}`);
console.log(`pars q = ${q.toString(2)}`);
console.log(`q len = ${q.toString(2).length}`);

let h = 2;
let g = Math.round(Math.pow(h, (p - 1) / q)) % p;

console.log(`\nq = ${q}`);
console.log(`p = ${p}`);
console.log(`h = ${h}`);
console.log(`g = ${g}`);

//------------------------------- Creating keys -------------------------------

let x =  Math.round(Math.random() * 5);
let y =  Math.pow(g, x) % p;

console.log(`\nx = ${x}`);
console.log(`y = ${y}`);


//------------------------------- Message signature -------------------------------

let k = 0;
let r = 0;

if (r == 0) reCalcR();

let bracket = (h + x * r)
let s = Math.round((Math.pow(k, -1) * bracket) % q)

if (s == 0) reCalcS();

console.log(`\nk = ${k}`);
console.log(`r = ${r}`);
console.log(`s = ${s}`);

let signature = { r, s };
console.log(`signature = (${signature.r}, ${signature.s})`);


//------------------------------- Signature verification -------------------------------

//let w = Math.round(Math.pow(s, -1) % q)

let w = 0; 

while (((s * w) % q) != 1) {
    w++;
}

let u1 = (hash * w) % q
let u2 = (r * w) % q

let powG = Math.round(Math.pow(g, u1))
let powY = Math.round(Math.pow(y, u2))

let v = Math.round(((powG * powY) % p) % q)

console.log(`\nw = ${w}`);
console.log(`u1 = ${u1}`);
console.log(`u2 = ${u2}`);
console.log(`v = ${v}`);

if(v == r) {
    console.log('\nCOOOOOOOOOOOOOOOOOOOOOOOOOOOLL');
}

//--------------------------------------------------------------------------------------
function reCalcR() {
    while (r == 0) {
        k = Math.round(Math.random() * q);
        r = Math.round((Math.pow(g, k) % p) % q)
    }
}

function reCalcS() {
    while (s == 0) {
        reCalcR();
        bracket = (hash + x * r)
        s = Math.round((Math.pow(k, -1) * bracket) % q)
    }
}

function getPrimeNumber() {

    let primeNum;
    let hashLen = hash.toString(2).length;
    for (let i = randMin; i <= randMax; i++) {
        let flag = 0;

        for (let j = 2; j < i; j++) {
            if (i % j == 0) {
                flag = 1;
                break;
            }
        }

        if (i > 1 && flag == 0) {
            primeNum = i;
            if (primeNum.toString(2).length == hashLen) { 
                return primeNum; 
            }
        }
    }
    return primeNum;
}

function getPrimeNumberP() {

    let primeNum;
    for (let i = randMin; i <= randMax; i++) {
        let flag = 0;

        for (let j = 2; j < i; j++) {
            if (i % j == 0) {
                flag = 1;
                break;
            }
        }

        if (i > 1 && flag == 0) {
            primeNum = i;
            if ((primeNum - 1) % q == 0) { 
                return primeNum; 
            }
        }
    }
    return primeNum;
}

function bigBig (a, b, sign){
    let aBig = BigInt(a);
    let bBig = BigInt(b);

    switch (sign) {
        case '+':
            return a + b;
            break;
        case '*':
            return a * b;
            break;
        case '-':
            return a - b;
            break;
        case '/':
            return a / b;
            break;
        case '%':
            return a % b;
            break;
        case 'a':
            return a;
            break;
        case 'b':
            return b;
            break;
        default:
            break;
    }
}