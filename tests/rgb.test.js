const { expect } = require('chai');
const lib = require('../build/Debug/lymuilm');

describe('Creating RGB test case', () => {
  it('Expect to create an RGB object', () => {
    const rgb = lib.makeRGB(5, 10, 95);

    expect(rgb.r).to.be.equal(5);
    expect(rgb.g).to.be.equal(10);
    expect(rgb.b).to.be.equal(95);
  });

  it('Expect to throw an error when argument less than required are pass', () => {
    expect(() => lib.makeRGB(10, 20)).to.throw('Missing arguments');
  });

  it('Expect to throw an error when wrong argument type is passed', () => {
    expect(() => lib.makeRGB('hello', 'i am', 'a bug')).to.throw('Wrong argument(s) type');
  });

  it('Expect to not throw when passing float value', () => {
    const rgb = lib.makeRGB(5.0, 10.0, 98.0);
    expect(rgb).to.be.deep.equal({
      r: 5,
      g: 10,
      b: 98
    });
  });

  it('Expect to throw an error when multiple wrong type is pass', () => {
    expect(() => lib.makeRGB('someone', 1.0, 'pokemon')).to.throw('Wrong argument(s) type');
  });

  it('Expect to create object even with more args than 3', () => {
    const rgb = lib.makeRGB(10.0, 5.0, 98, 95, 10);

    expect(rgb).to.be.deep.equal({
      r: 10,
      g: 5,
      b: 98
    });
  });

  it('Expect to not throw when a value > 255 is pass', () => {
    expect(() => lib.makeRGB(300, 400, 500)).to.not.throw();
  });

  it('Expect to throw when no param is pass', () => {
    expect(() => lib.makeRGB()).to.throw('Missing arguments');
  });
});
