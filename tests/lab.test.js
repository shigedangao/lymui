const { expect } = require('chai');
const SegfaultHandler = require('segfault-handler');
const lib = require('../build/Debug/lymuilib');

SegfaultHandler.registerHandler('convert.log');


describe('Creating LAB from RGB', () => {
  it('Expect to create LAB object from RGB', () => {
    const rgb = {
      r: 50,
      g: 10,
      b: 95
    };

    const lab = lib.convert({
      data: rgb,
      output: 'nLab',
      colorType: 'srgb'
    });
  });
});