const { expect } = require('chai');
const SegfaultHandler = require('segfault-handler');
const lib = require('../build/Debug/lymuilib');

SegfaultHandler.registerHandler('ycbcr_crash.log');

describe('Creating Ycbcr from RGB Object', () => {
  it('Expect to create Ycbcr object from RGB Object', () => {
    const rgb = {
      r: 0,
      g: 100,
      b: 200
    };

    const ycbcr = lib.getYcbcrFromRgb(rgb);
    expect(ycbcr).to.be.deep.equal({
      y: 86,
      cb: 187,
      cr: 77
    });
  });

  it('Expect to create Ycbcr object from RGB black value object', () => {
    const rgb = {
      r: 0,
      g: 0,
      b: 0
    };

    const ycbcr = lib.getYcbcrFromRgb(rgb);
    expect(ycbcr).to.be.deep.equal({
      y: 16,
      cb: 128,
      cr: 128
    });
  });

  it('Expect to create Ycbcr object from RGB white value object',() => {
    const rgb = {
      r: 255,
      g: 255,
      b: 255
    };

    const ycbcr = lib.getYcbcrFromRgb(rgb);
    expect(ycbcr).to.be.deep.equal({
      y: 235,
      cb: 128,
      cr: 128
    });
  });

  it('Expect to throw when no argument is pass', () => {
    expect(() => lib.getYcbcrFromRgb()).to.throw('Missing arguments')
  });

  it('Expect to throw when a missing prop is founded', () => {
    const rgb = {
      r: 1,
      b: 20
    };

    expect(() => lib.getYcbcrFromRgb(rgb)).to.throw('Property not found in JS Object');
  });

  it('Expect to throw native JS error when null is pass', () => {
    expect(() => lib.getYcbcrFromRgb(null)).to.throw('Cannot convert undefined or null to object');
  });
});

describe('Creating RGB from Ycbcr', () => {
  it('Expect to convert a Ycbcr to an RGB object', () => {
    const ycbcr = {
      y: 86,
      cb: 187,
      cr: 77
    };

    const rgb = lib.getRgbFromYcbcr(ycbcr);
    expect(rgb).to.be.deep.equal({
      r: 0,
      g: 100,
      // Note that the 201 value is due to the fact that the lib round the value to the nearest...
      b: 201
    });
  });

  it('Expect to retrieve a black value RGB object from YCbCr', () => {
    const ycbcr = {
      y: 16,
      cb: 128,
      cr: 128
    };

    const rgb = lib.getRgbFromYcbcr(ycbcr);
    expect(rgb).to.be.deep.equal({
      r: 0,
      g: 0,
      b: 0
    });
  });

  it('Expect to retrieve a white value RGB object from YCbCr', () => {
    const ycbcr = {
      y: 235,
      cb: 128,
      cr: 128
    };

    const rgb = lib.getRgbFromYcbcr(ycbcr);
    expect(rgb).to.be.deep.equal({
      r: 255,
      g: 255,
      b: 255
    });
  });

  it('Expect to throw when no param is pass', () => {
    expect(() => lib.getRgbFromYcbcr()).to.throw('Missing arguments');
  });

  it('Expect to throw when a missing param in object is pass', () => {
    const ycbcr = {
      y: 235,
      cr: 128
    };

    expect(() => lib.getRgbFromYcbcr(ycbcr)).to.throw('Property not found in JS Object');
  });

  it('Expect to throw when a missing param in object is pass', () => {
    const ycbcr = {
      y: 235,
      cb: 'lol',
      cr: 128
    };

    expect(() => lib.getRgbFromYcbcr(ycbcr)).to.throw('Error while creating C type');
  });
});
