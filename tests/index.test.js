const {yescrypt, YESCRYPT_RW, YESCRYPT_WORM} =require('..');

jest.setTimeout(300000);

test('Yescrypt', async () => {

    expect((await yescrypt(Buffer.from('p'), Buffer.from('s'), 16, 8, 1, 0, 0, 16)).toString('hex')).toBe(
        'c8c7ff1122b0b291c3f2608948782cd6',
    );
    expect((await yescrypt(Buffer.from('p'), Buffer.from('s'), 16, 8, 4, 0, 0, 16)).toString('hex')).toBe(
        'e2ad06a9340816659d45e0dd3d8260a6',
    );

    expect((await yescrypt(Buffer.from('p'), Buffer.from('s'), 16, 8, 1, 0, 0, 16, YESCRYPT_WORM)).toString('hex')).toBe(
        '9dd636c2d0bb92345286efdaf8a68cfc',
    );

    expect((await yescrypt(Buffer.from('p'), Buffer.from('s'), 16, 8, 4, 0, 0, 16, YESCRYPT_WORM)).toString('hex')).toBe(
        '28e64f65a134d187ed3b16d73973c820',
    );
    expect((await yescrypt(Buffer.from('p'), Buffer.from('s'), 16, 8, 1, 0, 0, 16, 0)).toString('hex')).toBe(
        '4efe92b5bba5ee1837b4b02b67dc2dbd',
    );

    expect((await yescrypt(Buffer.from('p'), Buffer.from('s'), 16, 8, 4, 0, 0, 16, 0)).toString('hex')).toBe(
        '3a84ecee9f4d433e8ef75aec28a5daa3',
    );

    expect((await yescrypt(Buffer.from('p'), Buffer.from('s'), 16384, 8, 1, 0, 0, 16, YESCRYPT_RW)).toString('hex')).toBe(
        '648a7f55b1f5f083c190829860e09d37',
    );
    expect((await yescrypt(Buffer.from('p'), Buffer.from('s'), 16384, 8, 4, 0, 0, 16, YESCRYPT_RW)).toString('hex')).toBe(
        'ca813c704119b47cbec20ac8faa72dfe',
    );

    expect((await yescrypt(Buffer.from('p'), Buffer.from('s'), 16384, 8, 1, 0, 0, 16, YESCRYPT_WORM)).toString('hex')).toBe(
        'd44199db46046d92fb844964c099caa7',
    );

    expect((await yescrypt(Buffer.from('p'), Buffer.from('s'), 16384, 8, 4, 0, 0, 16, YESCRYPT_WORM)).toString('hex')).toBe(
        '3d667b9a722cc915fbf008911c88ceca',
    );

    expect((await yescrypt(Buffer.from('p'), Buffer.from('s'), 16384, 8, 1, 0, 0, 16, 0)).toString('hex')).toBe(
        '4329787752e75d1de359a05806e492d4',
    );

    expect((await yescrypt(Buffer.from('p'), Buffer.from('s'), 16384, 8, 4, 0, 0, 16, 0)).toString('hex')).toBe(
        '949c1fb99e622cb8447b3b1dfd009cd2',
    );
});
