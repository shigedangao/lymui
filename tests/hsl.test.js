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
      l: 19.6
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
      l: 69.59
    });
  });

  it('Expect to throw when no param is passed', () => {
    expect(() => lib.getHslFromRgb()).to.throw('Missing arguments');
  });

  it('Expect to throw when missing props in rgb object', () => {
    const rgb = {
      r: 0,
      b: 100
    };

    expect(() => lib.getHslFromRgb(rgb)).to.throw('Property not found in JS Object');
  });

  it('Expect to throw when wrong kind of argument is passed', () => {
    expect(() => lib.getHslFromRgb('lol')).to.throw('Property not found in JS Object');
  });
});

describe('Creating RGB from HSL', () => {
  it('Expect to create RGB from HSL object', () => {
    const hsl = {
      h: 237,
      s: 90,
      l: 19.7
    };

    const rgb = lib.getRgbFromHsl(hsl);
    expect(rgb).to.be.deep.equal({
      r: 5,
      g: 9, // loss of precision somewhere due to floating points
      b: 95
    });
  });

  it('Expect to convert HSL black color to RGB object', () => {
    const hsl = {
      h: 0,
      s: 0,
      l: 0
    };

    const rgb = lib.getRgbFromHsl(hsl);
    expect(rgb).to.be.deep.equal({
      r: 0,
      g: 0,
      b: 0
    });
  });

  it('Expect to convert HSL white color to RGB object', () => {
    const hsl = {
      h: 0,
      s: 0,
      l: 100
    };

    const rgb = lib.getRgbFromHsl(hsl);
    expect(rgb).to.be.deep.equal({
      r: 255,
      g: 255,
      b: 255
    });
  });

  it('Expect to throw when missing property is founded in HSL object', () => {
    const hsl = {
      h: 200,
      l: 30
    };

    expect(() => lib.getRgbFromHsl(hsl)).to.throw('Property not found in JS Object');
  });

  it('Expect to throw when no argument is pass', () => {
    expect(() => lib.getRgbFromHsl()).to.throw('Missing arguments');
  });
});