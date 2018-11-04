const { expect } = require('chai');
const SegfaultHandler = require('segfault-handler');
const lib = require('../build/Debug/lymuilib');

SegfaultHandler.registerHandler('hsl_crash.log');

describe('Creating HSL from RGB', () => {
  it('Expect to create HSL object from RGB object', () => {
    const rgb = {
      r: 5,
      g: 10,
      b: 95
    };
    
    const hsl = lib.getHslFromRgb(rgb);
    expect(hsl).to.be.deep.equal({
      h: 237,
      s: 90,
      l: 19.5 // varied between 19.5 / 19.6
    });
  });

  it('Expect to create dark hsl', () => {
    const rgb = {
      r: 0,
      g: 0,
      b: 0
    };

    const hsl = lib.getHslFromRgb(rgb);
    expect(hsl).to.be.deep.equal({
      h: 0,
      s: 0,
      l: 0
    });
  });

  it('Expect to create a white hsl', () => {
    const rgb = {
      r: 255,
      g: 255,
      b: 255
    };

    const hsl = lib.getHslFromRgb(rgb);
    expect(hsl).to.be.deep.equal({
      h: 0,
      s: 0,
      l: 100
    });
  });

  it('Expect to create a high saturation hsl', () => {
    const rgb = {
      r: 100,
      g: 150,
      b: 255
    };

    const hsl = lib.getHslFromRgb(rgb);
    expect(hsl).to.be.deep.equal({
      h: 221,
      s: 100,
      l: 69.5
    });
  });

  it('Expect to throw when no param is pass', () => {
    expect(() => lib.getHslFromRgb()).to.throw('Missing arguments');
  });

  it('Expect to throw when missing props in rgb object', () => {
    const rgb = {
      r: 0,
      b: 100
    };

    expect(() => lib.getHslFromRgb(rgb)).to.throw('Property not found in JS Object');
  })
});