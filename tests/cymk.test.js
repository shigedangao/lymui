const SegfaultHandler = require('segfault-handler');
const { expect } = require('chai');
const lib = require('../build/Debug/lymuilib');

SegfaultHandler.registerHandler("crash.log");

describe('Creating Cymk from RGB', () => {
  it('Expect to create a Cymk object from a RGB object', () => {
    const rgb = {
      r: 5,
      g: 10,
      b: 198
    };

    const cymk = lib.getCymkFromRgb(rgb, 1000);
    expect(cymk).to.be.deep.equal({
      c: 0.973,
      y: 0,
      m: 0.949,
      k: 0.223
    });
  });

  it('Expect to create a cymk object from a black value RGB object', () => {
    const rgb = {
      r: 0,
      g: 0,
      b: 0
    };

    const cymk = lib.getCymkFromRgb(rgb, 1000);
    expect(cymk).to.be.deep.equal({
      c: 0,
      y: 0,
      m: 0,
      k: 1
    });
  });

  it('Expect to create a cymk object from a white value RGB object', () => {
    const rgb = {
      r: 255,
      g: 255,
      b: 255
    };

    const cymk = lib.getCymkFromRgb(rgb, 1000);
    expect(cymk).to.be.deep.equal({
      c: 0,
      y: 0,
      m: 0,
      k: 0
    });
  });

  it('Expect method to not throw when bad rgb value is pass', () => {
    const rgb = {
      r: 300,
      g: 300,
      b: 500
    };

    expect(() => lib.getCymkFromRgb(rgb, 10000)).to.not.throw();
  });

  it('Expect to round the value with default parameter', () => {
    const rgb = {
      r: 5,
      g: 10,
      b: 198
    };

    const cymk = lib.getCymkFromRgb(rgb);
    expect(cymk).to.be.deep.equal({
      c: 0.973,
      y: 0,
      m: 0.949,
      k: 0.223
    });
  });

  it('Expect to throw when no rgb object is pass', () => {
    expect(() => lib.getCymkFromRgb()).to.throw('Missing arguments');
  });

  it('Expect to throw when no rgb object is pass', () => {
    expect(() => lib.getCymkFromRgb({
      b: 10
    })).to.throw('Property not found in JS Object');
  });
});

describe('Creation of a RGB object from a CYMK object', () => {
  it('Expect create RGB Object from CYMK Object', () => {
    const cymk = {
      c: 0.973,
      y: 0,
      m: 0.949,
      k: 0.223
    };

    const rgb = lib.getRgbFromCymk(cymk);
    expect(rgb).to.be.deep.equal({
      r: 5,
      g: 10,
      b: 198
    });
  });

  it('Expect to create RGB Object from Black CYMK object', () => {
    const cymk = {
      c: 0,
      y: 0,
      m: 0,
      k: 1
    };

    const rgb = lib.getRgbFromCymk(cymk);
    expect(rgb).to.be.deep.equal({
      r: 0,
      g: 0,
      b: 0
    });
  });

  it('Expect to create RGB Object from White CYMK object', () => {
    const cymk = {
      c: 0,
      y: 0,
      m: 0,
      k: 0
    };

    const rgb = lib.getRgbFromCymk(cymk);
    expect(rgb).to.be.deep.equal({
      r: 255,
      g: 255,
      b: 255
    });
  });

  it('Expect to throw when no param is pass', () => {
    expect(() => lib.getRgbFromCymk()).to.throw('Missing arguments');
  });

  it('Expect to throw when a wrong cymk object is pass', () => {
    const cymk = {
      y: 0,
      m: 0,
      k: 0
    };

    expect(() => lib.getRgbFromCymk(cymk)).to.throw('Property not found in JS Object');
  });

  it('Expect to throw when a param is of the wrong type', () => {
    const cymk = {
      c: 'lol',
      y: 0,
      m: 0,
      k: 0
    };

    expect(() => lib.getRgbFromCymk(cymk)).to.throw('Error while creating C type');
  });
});