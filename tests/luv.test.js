const { expect } = require('chai');
const SegfaultHandler = require('segfault-handler');
const lib = require('../build/Debug/lymuilib');

SegfaultHandler.registerHandler('lch_convert.log');

describe('Creating LCH from RGB', () => {
  it('Expect to create LCH from RGB with type SRGB', async () => {
    const rgb = {
      r: 5,
      g: 10,
      b: 98
    };

    const luv = await lib.convert({
      data: rgb,
      output: 'luv',
      colorType: 'srgb'
    });

    expect(luv).to.be.deep.equal({
      l: 10.0301,
      u: -2.9729,
      v: -36.6297
    });
  });

  it('Expect to create LCH from RGB with type ARGB', async () => {
    const rgb = {
      r: 5,
      g: 10,
      b: 98
    };

    const luv = await lib.convert({
      data: rgb,
      output: 'luv',
      colorType: 'adobeRgb'
    });

    expect(luv).to.be.deep.equal({
      l: 8.7716,
      u: -2.6738,
      v: -34.6343
    });
  });

  it('Expect to create a valid LCH from a white RGB', async () => {
    const rgb = {
      r: 100,
      g: 100,
      b: 100
    };

    const luv = await lib.convert({
      data: rgb,
      output: 'luv',
      colorType: 'srgb'
    });

    expect(luv).to.be.deep.equal({
      l: 42.3707,
      u: 0.0006,
      v: -0.0039
    });
  });

  it('Expect to create a valid LCH from a white RGB', async () => {
    const rgb = {
      r: 255,
      g: 255,
      b: 255
    };

    const luv = await lib.convert({
      data: rgb,
      output: 'luv',
      colorType: 'adobeRgb'
    });

    expect(luv).to.be.deep.equal({
      l: 99.9922,
      u: 0.0016,
      v: -0.009
    });
  });
});