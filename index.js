const binding = require('bindings')('binding');
const YESCRYPT_WORM=1;
const YESCRYPT_RW=2;
const yescrypt = (ps, s, n, r, p, t, g, len, flag=YESCRYPT_RW) => {
    return new Promise((resolve, reject) => binding.yescrypt(Buffer.from(ps), Buffer.from(s), n, r,p, t, g, len, flag, (e, r)=> {
        if (e) {
            return reject(e);
        }
        return resolve(Buffer.from(r));
    }))
}

module.exports = {
    yescrypt,
    YESCRYPT_WORM,
    YESCRYPT_RW
}
