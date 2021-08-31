export declare const YESCRYPT_RW = 2;
export declare const YESCRYPT_WORM = 1;
export declare function yescrypt(password: string | Buffer, salt: string | Buffer, N: number, r: number, p: number, t: number, g: number, dkLen: number, flags?: number): Promise<Buffer>;
//# sourceMappingURL=index.d.ts.map