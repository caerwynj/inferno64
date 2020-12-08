Arrays: module
{
	PATH:	con "/dis/lib/arrays.dis";

	filter:		fn[T](a: array of T, f: ref fn(x: T): int): array of T;

	map:		fn[T](a₀: array of T, f: ref fn(x: T): T): array of T;

	pair:		fn[T₁, T₂](a₁: array of T₁, a₂: array of T₂): array of (T₁, T₂);

	find:		fn[T](a: array of T, x: T): array of T
					for {	T =>	Equals:	fn(a, b: T): int;	};

	prepend:	fn[T](a₀: array of T, x: T): array of T;

	append:		fn[T](a₀: array of T, x: T): array of T;

	tail:		fn[T](a: array of T): array of T;

	# Return a pretty string representing the array
	stringify:	fn[T](a: array of T): string
					for {	T =>	String:	fn(a: self T): string;	};

};
