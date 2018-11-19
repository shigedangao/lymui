const { expect } = require('chai');
const SegfaultHandler = require('segfault-handler');
const lib = require('../build/Debug/lymuilib');

SegfaultHandler.registerHandler('lch_convert.log');

describe('Creating LUV from RGB', () => {
  it('Expect to create LUV from RGB with type SRGB', async () => {
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

  it('Expect to create LUV from RGB with type ARGB', async () => {
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

  it('Expect to create a valid LUV from a white SRGB', async () => {
    const rgb = {
      r: 255,
      g: 255,
      b: 255
    };

    const luv = await lib.convert({
      data: rgb,
      output: 'luv',
      colorType: 'srgb'
    });

    expect(luv).to.be.deep.equal({
      l: 100,
      u: 0,
      v: 0
    });
  });

  it('Expect to create a valid LUV from a white ARGB', async () => {
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
      l: 100,
      u: 0,
      v: 0
    });
  });

  it('Expect to throw when a params is missing on the Rgb object', async () => {
    try {
      await lib.convert({
        output: 'luv',
        colorType: 'srgb'
      });
    } catch (e) {
      expect(e).to.be.deep.equal({
        err: 'Property not found in JS Object'
      });
    }
  });

  it('Expect to throw when a params is missing on the Rgb object', async () => {
    const xyz = {
      x: 0.03628,
      y: 0.01777,
      z: 0.11705
    };
    
    const luv = await lib.convert({
      data: xyz,
      output: 'luv',
    });

    expect(luv).to.be.deep.equal({
      l: 14.2705,
      u: 4.4641,
      v: -41.5165
    });
  });
});