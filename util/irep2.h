#include <vector>

#include <big-int/bigint.hh>

/** Base class for all types */
class type2t
{
protected:
  type2t(type_ids id);
  type2t(const type2t &ref);

public:
  /** Enumeration identifying each sort of type.
   *  The idea being that we might (for whatever reason) at runtime need to fall
   *  back onto identifying a type through just one field, for some reason. It's
   *  also highly useful for debugging */
  enum type_ids {
  };

  /** Instance of type_ids recording this types type. */
  type_ids type_id;
};

/** Base class for all expressions */
class expr2t
{
protected:
  expr2t(type2t &type, expr_ids id);
  expr2t(const expr2t &ref);

public:
  /** Enumeration identifying each sort of expr.
   *  The idea being to permit runtime identification of a type, for debugging or
   *  otherwise. See type2t::type_ids. */
  enum expr_ids {
  };

  /** Clone method. Entirely self explanatory */
  virtual expr2t *clone(void) const = 0;

  /** Instance of expr_ids recording tihs exprs type. */
  expr_ids expr_id;

  /** Type of this expr. All exprs have a type. */
  const type2t &type;
};

/** Constant class type. Not designed to contain any piece of data or method in
 *  particular, but allows for additional type safety. */
class constant2t : expr2t
{
protected:
  constant2t(type2t &type, expr_ids id);
  constant2t(const constant2t &ref);

public:
  /** Clone method. Entirely self explanatory */
  virtual expr2t *clone(void) const = 0;
};

/** Constant integer class. Records a constant integer of an arbitary
 *  precision */
class constant_int2t : constant2t
{
protected:
  constant_int2t(const BigInt &input);
  constant_int2t(const constant_int2t &ref);

  /** Concrete clone implementation. */
  virtual expr2t *clone(void) const;

  /** Arbitary precision integer record. */
  BigInt constant_value;
};

/** Constant class for string constants. */
class constant_string2t : constant2t
{
protected:
  constant_string2t(const std::string stringref &ref);
  constant_string2t(const constant_string2t &ref);

public:
  /** Concrete clone implementation. */
  virtual expr2t *clone(void) const;

  /** Arbitary precision integer record. */
  const std::string value;
};

/** Const datatype - for holding structs and unions */
class constant_datatype2t : constant2t
{
protected:
  constant_datatype2t(const type2t &type, const std::vector<exprt *> &members);
  constant_datatype2t(const constant_datatype2t &ref);

public:
  virtual expr2t *clone(void) const = 0;

  std::vector<exprt *> datatype_members;
};

class constant_struct2t : constant_datatype2t
{
protected:
  constant_struct2t(const type2t &type, const std::vector<exprt *> &members);
  constant_struct2t(const constant_struct2t &ref);

public:
  virtual expr2t *clone(void) const;
};

class constant_union2t : constant_datatype2t
{
protected:
  constant_union2t(const type2t &type, const std::vector<exprt *> &members);
  constant_union2t(const constant_union2t &ref);

public:
  virtual expr2t *clone(void) const;
};

class constant_array2t : constant2t
{
protected:
  constant_array2t(const type2t &type, const std::vector<exprt *> &members);
  constant_array2t(const constant_array2t &ref);

public:
  virtual expr2t *clone(void) const;

  std::vector<exprt *> datatype_members;
};

class constant_array_of2t : constant2t
{
protected:
  constant_array2t(const type2t &type, const expr2t *initializer);
  constant_array2t(const constant_array_of2t &ref);

public:
  virtual expr2t *clone(void) const;

  // Type records the size of the array; this records the initializer.
  const exprt *initializer;
};

class symbol2t : expr2t
{
protected:
  symbol2t(const type2t &type, const std::string &name);
  symbol2t(const symbol2t &ref);

public:
  virtual expr2t *clone(void) const;

  // Symbol name - only so long as a symbol is a string. In the future, this
  // should really really change.
  const std::string name;
};

class typecast2t : expr2t
{
protected:
  typecast2t(const type2t &type, const expr2t &expr);
  typecast2t(const typecast2t &ref);

public:
  virtual expr2t *clone(void) const;

  // Expression to typecast from.
  const expr2t &from;
};

class if2t : expr2t
{
protected:
  if2t(const type2t &type, const expr2t &cond, const expr2t &true_val,
             const expr2t &false_val);
  if2t(const if2t &ref);

public:
  virtual expr2t *clone(void) const;

  // Conditional that this "if" depends on, and which value to take upon each
  // branch of that condition.
  const expr2t &cond;
  const expr2t &true_value;
  const expr2t &false_value;
};

/** Relation superclass.
 *  All subclasses should be relation operators -- ie, equality, lt, ge, so
 *  forth. Stores two expressions (of the _same_ _type_), always has result
 *  type of a bool. */
class rel2t : expr2t
{
protected:
  rel2t(const expr2t &val1, const expr2t &val2);
  rel2t(const rel2t &ref);

public:
  virtual expr2t *clone(void) const;

  const expr2t &side_1;
  const expr2t &side_2;
};

class equality2t : rel2t
{
protected:
  equality2t(const expr2t &val1, const expr2t &val2);
  equality2t(const equality2t &ref);

public:
  virtual expr2t *clone(void) const;
};

class notequal2t : rel2t
{
protected:
  notequal2t(const expr2t &val1, const expr2t &val2);
  notequal2t(const notequal2t &ref);

public:
  virtual expr2t *clone(void) const;
};

class lessthan2t : rel2t
{
protected:
  lessthan2t(const expr2t &val1, const expr2t &val2);
  lessthan2t(const lessthan2t &ref);

public:
  virtual expr2t *clone(void) const;
};

class greaterthan2t : rel2t
{
protected:
  greaterthan2t(const expr2t &val1, const expr2t &val2);
  greaterthan2t(const greaterthan2t &ref);

public:
  virtual expr2t *clone(void) const;
};

class lessthanequal2t : rel2t
{
protected:
  lessthanequal2t(const expr2t &val1, const expr2t &val2);
  lessthanequal2t(const lessthanequal2t &ref);

public:
  virtual expr2t *clone(void) const;
};

class greaterthanequal2t : rel2t
{
protected:
  greaterthanequal2t(const expr2t &val1, const expr2t &val2);
  greaterthanequal2t(const greaterthanequal2t &ref);

public:
  virtual expr2t *clone(void) const;
};

/** Logical operations base class. Base for any logical operator. No storage in
 *  this particular class. Result is always of boolean type. */
class lops2t : expr2t
{
protected:
  lops2t(void);
  lops2t(const lops2t &ref);

public:
  virtual expr2t *clone(void) const;
};

/** Not operator. Takes a boolean value; results in a boolean value. */
class not2t : lops2t
{
protected:
  not2t(const expr2t &notval);
  not2t(const not2t &ref);

public:
  virtual expr2t *clone(void) const;

  const exprt &notvalue;
};

/** Base class for 2-operand boolean oeprators. Always results in a boolean,
 *  takes two operands, both of boolean type. */
class logical_2ops2t : lops2t
{
protected:
  logical_2ops2t(const expr2t &val1, const expr2t &val2);
  logical_2ops2t(const logical_2ops2t &ref);

public:
  virtual expr2t *clone(void) const;

  const exprt &side_1;
  const exprt &side_2;
};

class and2t : logical_2ops2t
{
protected:
  and2t(const expr2t &val1, const expr2t &val2);
  and2t(const and2t &ref);

public:
  virtual expr2t *clone(void) const;
};

class or2t : logical_2ops2t
{
protected:
  or2t(const expr2t &val1, const expr2t &val2);
  or2t(const or2t &ref);

public:
  virtual expr2t *clone(void) const;
};

class xor2t : logical_2ops2t
{
protected:
  xor2t(const expr2t &val1, const expr2t &val2);
  xor2t(const xor2t &ref);

public:
  virtual expr2t *clone(void) const;
};

/** Binary operations base class. Take a type, probably integer with a width,
 *  and some operands. */
class binops2t : expr2t
{
protected:
  binops2t(const type2t &type, const expr2t &val1, const expr2t &val2);
  binops2t(const binops2t &ref);

public:
  virtual expr2t *clone(void) const;

  const expr2t &side_1;
  const expr2t &side_2;
};

class bitand2t : binops2t
{
protected:
  bitand2t(const type2t &type, const expr2t &val1, const expr2t &val2);
  bitand2t(const bitand2t &ref);

public:
  virtual expr2t *clone(void) const;
};

class bitor2t : binops2t
{
protected:
  bitor2t(const type2t &type, const expr2t &val1, const expr2t &val2);
  bitor2t(const bitor2t &ref);

public:
  virtual expr2t *clone(void) const;
};

class bitxor2t : binops2t
{
protected:
  bitxor2t(const type2t &type, const expr2t &val1, const expr2t &val2);
  bitxor2t(const bitxor2t &ref);

public:
  virtual expr2t *clone(void) const;
};

class bitnand2t : binops2t
{
protected:
  bitnand2t(const type2t &type, const expr2t &val1, const expr2t &val2);
  bitnand2t(const bitnand2t &ref);

public:
  virtual expr2t *clone(void) const;
};

class bitnor2t : binops2t
{
protected:
  bitnor2t(const type2t &type, const expr2t &val1, const expr2t &val2);
  bitnor2t(const bitnor2t &ref);

public:
  virtual expr2t *clone(void) const;
};

class bitnxor2t : binops2t
{
protected:
  bitnxor2t(const type2t &type, const expr2t &val1, const expr2t &val2);
  bitnxor2t(const bitnxor2t &ref);

public:
  virtual expr2t *clone(void) const;
};

class lshr2t : binops2t
{
protected:
  lshr2t(const type2t &type, const expr2t &val1, const expr2t &val2);
  lshr2t(const lshr2t &ref);

public:
  virtual expr2t *clone(void) const;
};
