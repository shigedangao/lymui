const { expect } = require('chai');
const SegfaultHandler = require('segfault-handler');
const lib = require('../build/Debug/lymuilib');

SegfaultHandler.registerHandler('hsv_crash.log');

describe('Creating HSV Object from RGB', () => {
  it('Expect to create HSV from RGB Object', () => {
    const rgb = {
      r: 5,
      g: 10,
      b: 98
    };

    const hsv = lib.getHsvFromRgb(rgb);
    expect(hsv).to.be.deep.equal({
      h: 237,
      s: 94.9,
      v: 38.4
    });
  });

  it('Expect to create black HSV from RGB Object', () => {
    const rgb = {
      r: 0,
      g: 0,
      b: 0
    };

    const hsv = lib.getHsvFromRgb(rgb);
    expect(hsv).to.be.deep.equal({
      h: 0,
      s: 0,
      v: 0
    });
  });

  it('Expect to create white HSV from RGB Object', () => {
    const rgb = {
      r: 255,
      g: 255,
      b: 255
    };

    const hsv = lib.getHsvFromRgb(rgb);
    expect(hsv).to.be.deep.equal({
      h: 0,
      s: 0,
      v: 100
    });
  });

  it('Expect to create a HSV object from RGB', () => {
    const rgb = {
      r: 100,
      g: 200,
      b: 120
    };

    const hsv = lib.getHsvFromRgb(rgb);
    expect(hsv).to.be.deep.equal({
      h: 132,
      s: 50,
      v: 78.4
    });
  });

  it('Expect to throw when no param is pass', () => {
    expect(() => lib.getHsvFromRgb()).to.throw('Missing arguments');
  });

  it('Expect to throw when missing props in rgb object', () => {
    const rgb = {
      r: 0,
      b: 100
    };

    expect(() => lib.getHsvFromRgb(rgb)).to.throw('Property not found in JS Object');
  });

  it('Expect to throw when wrong kind of argument is passed', () => {
    expect(() => lib.getHsvFromRgb('lol')).to.throw('Property not found in JS Object');
  });
});

describe('Creating RGB Object from HSV Object', () => {
  it('Creating RGB from HSV', () => {
    const hsv = {
      h: 237,
      s: 94.9,
      v: 38.4
    };

    const rgb = lib.getRgbFromHsv(hsv);
    expect(rgb).to.be.deep.equal({
      r: 5,
      g: 10,
      b: 98
    });
  });

  it('Creating RGB from HSV', () => {
    const hsv = {
      h: 237,
      s: 94.7,
      v: 37.3
    };

    const rgb = lib.getRgbFromHsv(hsv);
    expect(rgb).to.be.deep.equal({
      r: 5,
      g: 10,
      b: 95
    });
  });


  it('Creating black RGB from HSV', () => {
    const hsv = {
      h: 0,
      s: 0,
      v: 0
    };

    const rgb = lib.getRgbFromHsv(hsv);
    expect(rgb).to.be.deep.equal({
      r: 0,
      g: 0,
      b: 0
    });
  });

  it('Creating white RGB from HSV', () => {
    const hsv = {
      h: 0,
      s: 0,
      v: 100
    };

    const rgb = lib.getRgbFromHsv(hsv);
    expect(rgb).to.be.deep.equal({
      r: 255,
      g: 255,
      b: 255
    });
  });

  it('Expect to throw when missing property is founded in HSV object', () => {
    const hsv = {
      h: 200,
      v: 30
    };

    expect(() => lib.getRgbFromHsv(hsv)).to.throw('Property not found in JS Object');
  });

  it('Expect to throw when no argument is pass', () => {
    expect(() => lib.getRgbFromHsv()).to.throw('Missing arguments');
  });
});