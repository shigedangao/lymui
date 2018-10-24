const { expect } = require('chai');
const lib = require('../build/Debug/lymuilm');

describe('RGB test case', () => {
  it('Expect to create an RGB object', () => {
    const rgb = lib.MakeRGB(5, 10, 95);

    expect(rgb.r).to.be.equal(5);
    expect(rgb.g).to.be.equal(10);
    expect(rgb.b).to.be.equal(95);
  });
});