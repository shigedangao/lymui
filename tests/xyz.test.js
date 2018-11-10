const { expect } = require('chai');
const SegfaultHandler = require('segfault-handler');
const lib = require('../build/Debug/lymuilib');

SegfaultHandler.registerHandler('xyz_crash.log');

describe('Creating Xyz from RGB', () => {
  it('Expect to create XYZ from RGB Object', () => {
    const rgb = {
      r: 50,
      g: 10,
      b: 95
    };

    const xyz = lib.getXyzFromRgb(rgb, "srgb", 10000);
    expect(xyz).to.be.deep.equal({
      x: 0.0348,
      y: 0.0172,
      z: 0.1097
    });
  });

  it('Expect to create XYZ from RGB Object', () => {
    const rgb = {
      r: 50,
      g: 10,
      b: 95
    };

    const xyz = lib.getXyzFromRgb(rgb, "adobeRgb", 10000);
    expect(xyz).to.be.deep.equal({
      x: 0.0376,
      y: 0.0173,
      z: 0.1138
    });
  });

  it('Expect to create dark XYZ from RGB Object of type SRGB', () => {
    const rgb = {
      r: 0,
      g: 0,
      b: 0
    };

    const xyz = lib.getXyzFromRgb(rgb, "srgb", 10000);
    expect(xyz).to.be.deep.equal({
      x: 0,
      y: 0,
      z: 0
    });
  });

  it('Expect to create dark XYZ from RGB Object of type adobe RGB', () => {
    const rgb = {
      r: 0,
      g: 0,
      b: 0
    };

    const xyz = lib.getXyzFromRgb(rgb, "adobeRgb", 10000);
    expect(xyz).to.be.deep.equal({
      x: 0,
      y: 0,
      z: 0
    });
  });

  it('Expect to create bright XYZ from RGB Object of type SRGB', () => {
    const rgb = {
      r: 255,
      g: 255,
      b: 255
    };

    const xyz = lib.getXyzFromRgb(rgb, "srgb", 10000);
    expect(xyz).to.be.deep.equal({
      x: 0.9502,
      y: 0.9997,
      z: 1
    });
  });

  it('Expect to create dark XYZ from RGB Object of type adobe RGB', () => {
    const rgb = {
      r: 255,
      g: 255,
      b: 255
    };

    const xyz = lib.getXyzFromRgb(rgb, "adobeRgb", 10000);
    expect(xyz).to.be.deep.equal({
      x: 0.9502,
      y: 0.9998,
      z: 1.0887
    });
  });

  it('Expect to throw when the color type property is missing', () => {
    const rgb = {
      r: 50,
      g: 30,
      b: 100,
    };

    expect(() => lib.getXyzFromRgb(rgb)).to.throw('Missing arguments');
  });

  it('Expect to throw when nothing is pass', () => {
    expect(() => lib.getXyzFromRgb()).to.throw('Missing arguments');
  });

  it('Expect to throw when the color type property is missing', () => {
    const rgb = {
      r: 50,
      b: 100,
    };

    expect(() => lib.getXyzFromRgb(rgb, "adobeRgb")).to.throw('Property not found in JS Object');
  });
});