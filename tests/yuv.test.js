const { expect } = require('chai');
const SegfaultHandler = require('segfault-handler');
const lib = require('../build/Debug/lymuilib');

SegfaultHandler.registerHandler('yuv_crash.log');

describe('Creating YUV from RGB', () => {
  it('Expect to create YUV from RGB', () => {
    const rgb = {
      r: 50,
      g: 10,
      b: 95
    };

    const yuv = lib.getYuvFromRgb(rgb);
    expect(yuv).to.be.deep.equal({
      y: 0.123,
      u: 0.122,
      v: 0.063
    });
  });

  it('Expect to create dark YUV from black RGB', () => {
    const rgb = {
      r: 0,
      g: 0,
      b: 0
    };

    const yuv = lib.getYuvFromRgb(rgb);
    expect(yuv).to.be.deep.equal({
      y: 0,
      u: 0,
      v: 0
    });
  });

  it('Expect to create white YUV from white RGB', () => {
    const rgb = {
      r: 255,
      g: 255,
      b: 255
    };

    const yuv = lib.getYuvFromRgb(rgb);
    expect(yuv).to.be.deep.equal({
      y: 1,
      u: 0,
      v: 0
    });
  });

  it('Expect to throw when no arguments is pass', () => {
    expect(() => lib.getYuvFromRgb()).to.throw('Missing arguments');
  });

  it('Expect to throw when wrong kind of RGB is pass', () => {
    const rgb = {
      r: 10,
      g: 10
    };

    expect(() => lib.getYuvFromRgb(rgb)).to.throw('Property not found in JS Object');
  });

  it('Expect to create clamp YUV value', () => {
    const rgb = {
      r: 50,
      g: 10,
      b: 95
    };

    const yuv = lib.getYuvFromRgb(rgb, 100);
    expect(yuv).to.be.deep.equal({
      y: 0.12,
      u: 0.12,
      v: 0.06
    });
  });
});

describe('Creating RGB from YUV', () => {
  it('Expect to create RGB from YUV value', () => {
    const yuv = {
      y: 0.123,
      u: 0.122,
      v: 0.063
    };

    const rgb = lib.getRgbFromYuv(yuv);
    expect(rgb).to.be.deep.equal({
      r: 50,
      g: 10,
      b: 95
    });
  });

  it('Expect to create black RGB from dark YUV value', () => {
    const yuv = {
      y: 0,
      u: 0,
      v: 0
    };

    const rgb = lib.getRgbFromYuv(yuv);
    expect(rgb).to.be.deep.equal({
      r: 0,
      g: 0,
      b: 0
    });
  });

  it('Expect to create white RGB from bright YUV value', () => {
    const yuv = {
      y: 1,
      u: 0,
      v: 0
    };

    const rgb = lib.getRgbFromYuv(yuv);
    expect(rgb).to.be.deep.equal({
      r: 255,
      g: 255,
      b: 255
    });
  });

  it('Expect to throw when no param is passed', () => {
    expect(() => lib.getRgbFromYuv()).to.throw('Missing arguments');
  });

  it('Expect to throw when missing property in the YUV object is pass', () => {
    const yuv = {
      u: 0,
      v: 0
    };
    
    expect(() => lib.getRgbFromYuv(yuv)).to.throw('Property not found in JS Object');
  });

  it('Expect to throw when wrong kind of object is passed', () => {    
    expect(() => lib.getRgbFromYuv('lol')).to.throw('Property not found in JS Object');
  });
});