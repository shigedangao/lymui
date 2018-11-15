const { expect } = require('chai');
const SegfaultHandler = require('segfault-handler');
const lib = require('../build/Debug/lymuilib');

SegfaultHandler.registerHandler('convert.log');


describe('Creating LAB from RGB', () => {
  it('Expect to create LAB object from RGB with type SRGB', async () => {
    const rgb = {
      r: 50,
      g: 10,
      b: 95
    };

    const lab = await lib.convert({
      data: rgb,
      output: 'lab',
      colorType: 'srgb'
    });

    expect(lab).to.be.deep.equal({
      l: 0.1553,
      a: 0.7591,
      b: -1.3016
    });
  });

  it('Expect to create LAB object from RGB with type AdobeRGB', async () => {
    const rgb = {
      r: 50,
      g: 10,
      b: 95
    };

    const lab = await lib.convert({
      data: rgb,
      output: 'lab',
      colorType: 'adobeRgb'
    });

    expect(lab).to.be.deep.equal({
      l: 0.1566,
      a: 0.8659,
      b: -1.3577
    });
  });

  it('Expect to throw when nothing is passed', async () => {
    try {
      await lib.convert();
    } catch(e) {
      expect(e).to.be.deep.equal({
        err: 'Missing arguments'
      });
    }
  });

  it('Expect to throw when param data is missing', async () => {
    try {
      await lib.convert({
        output: 'lab',
        colorType: 'adobeRgb'
      });
    } catch(e) {
      expect(e).to.be.deep.equal({
        err: 'Property not found in JS Object'
      });
    }
  });

  it('Expect to throw when output data missing', async () => {
    const rgb = {
      r: 50,
      g: 10,
      b: 95
    };
    
    try {
      await lib.convert({
        data: rgb,
        colorType: 'adobeRgb'
      });
    } catch(e) {
      expect(e).to.be.deep.equal({
        err: 'Property not found in JS Object'
      });
    }
  });

  it('Expect to return a Lab object when xyz is pass', async () => {
    const xyz = {
      x: 0.0348,
      y: 0.0172,
      z: 0.1097
    };
    
    const lab = await lib.convert({
      data: xyz,
      output: 'lab'
    });

    // Note there are some precision difference as the output xyz is less precise
    // Than the one calculate by the rgb
    expect(lab).to.be.deep.equal({
      l: 0.1553,
      a: 0.7558,
      b: -1.3013
    });
  });

});