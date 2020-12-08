implement Arrays;

include "arrays.m";

# Return the array 'a' for which 'f' is fulfilled on its contents
filter[T](a: array of T, f: ref fn(x: T): int): array of T {
	if(a == nil)
		return nil;

	if(f(a[0]))
		return prepend(filter(tail(a), f), a[0]);

	if(len a < 2)
		return nil;

	return filter(tail(a), f);
}

# Return the array 'a₀' with the function 'f' applied to its contents
map[T](a₀: array of T, f: ref fn(x: T): T): array of T {
	if(a₀ == nil)
		return nil;

	a₁ := array[len a₀] of T;

	for(i := 0; i < len a₀; i++)
		a₁[i] = f(a₀[i]);

	return a₁;
}

# Create an array whose contents are the pairs of two equally-sized arrays
pair[T₁, T₂](a₁: array of T₁, a₂: array of T₂): array of (T₁, T₂) {
	if(a₁ == nil || a₂ == nil || len a₁ != len a₂)
		return nil;

	a₃ := array[len a₁] of (T₁, T₂);

	for(i := 0; i < len a₁; i++)
		a₃[i] = (a₁[i], a₂[i]);

	return a₃;
}

# Find instance of 'x' in 'l', return tail of 'l' from and including 'x'
find[T](a: array of T, x: T): array of T
	for {
		T =>	Equals:	fn(a, b: T): int;
	}
{
	for(i := 0; i < len a; i++)
		if(T.Equals(x, a[i]))
			return tail(a[i:]);

	return nil;
}

# Return the array 'a₀' with 'x' prepended
prepend[T](a₀: array of T, x: T): array of T {
	if(a₀ == nil)
		return array[1] of { * => x };

	a₁ := array[len a₀ + 1] of T;
	a₁[0] = x;

	for(i := 1; i < len a₁; i++)
		a₁[i] = a₀[i-1];

	return a₁;
}

# Return the array 'a₀' with 'x' appended
append[T](a₀: array of T, x: T): array of T {
	if(a₀ == nil)
		return array[1] of { * => x };

	a₁ := array[len a₀ + 1] of T;
	a₁[len a₁ - 1] = x;

	for(i := 0; i < len a₁ -1; i++)
		a₁[i] = a₀[i];

	return a₁;
}

# Return 'a[1:]' if possible, or nil
tail[T](a: array of T): array of T {
	if(a == nil || len a < 2)
		return nil;

	return a[1:];
}

# Return a pretty string representing the array
stringify[T](a: array of T): string
	for {
		T =>	String:	fn(a: self T): string;
	}
{
	if(a == nil) {
		return "[]\n";
	}

	s := "[";

	for(i := 0; i < len a; i++) {
		s += a[i].String();

		if(i < len a - 1)
			s += ", ";
	}

	return s + "]\n";
}
