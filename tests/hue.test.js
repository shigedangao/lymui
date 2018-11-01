const { expect } = require('chai');
const SegfaultHandler = require('segfault-handler');
const lib = require('../build/Debug/lymuilib');

SegfaultHandler.registerHandler('hue_crash.log');

describe('Creating Hue from RGB', () => {
  it('Expect to create a Hue value from an RGB Object', () => {
    const rgb = {
      r: 5,
      g: 195,
      b: 198
    };

    const hue = lib.getHueFromRgb(rgb);
    expect(hue).to.be.equal(181);
  });

  it('Expect to create a hue = 0 from black value RGB Object', () => {
    const rgb = {
      r: 0,
      g: 0,
      b: 0
    };

    const hue = lib.getHueFromRgb(rgb);
    expect(hue).to.be.equal(0);
  });

  it('Expect to create a hue = 0 from white RGB Object', () => {
    const rgb = {
      r: 1,
      g: 1,
      b: 1
    };

    const hue = lib.getHueFromRgb(rgb);
    expect(hue).to.be.equal(0);
  });

  it('Expect to create to not throw when creating a hue with a bad rgb object', () => {
    const rgb = {
      r: 200,
      g: 500,
      b: 900
    };

    expect(() => lib.getHueFromRgb(rgb)).to.not.throw();
  });

  it('Expect to throw when nothing is pass to the method', () => {
    expect(() => lib.getHueFromRgb()).to.throw('Missing arguments')
  });

  it('Expect to throw when passing wrong kind of param', () => {
    expect(() => lib.getHueFromRgb('hello')).to.throw('Property not found in JS Object');
  });
});