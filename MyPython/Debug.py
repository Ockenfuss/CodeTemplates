

def debug(func): 
    def debug_wrapper(*args, **kwargs):
        args_repr=[repr(a) for a in args]
        kwargs_repr = [f"{k}={v!r}" for k, v in kwargs.items()]  # 2
        signature = ", ".join(args_repr + kwargs_repr)           # 3
        print(f"Calling {func.__name__}({signature})")
        value = func(*args, **kwargs)
        print(f"{func.__name__!r} returned {value}")           # 4
        return value
    return debug_wrapper
