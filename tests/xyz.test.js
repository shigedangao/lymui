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
});