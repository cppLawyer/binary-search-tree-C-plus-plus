// queue standard header

// Copyright (c) Microsoft Corporation.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once
#ifndef _QUEUE_
#define _QUEUE_
#include <yvals_core.h>
#if _STL_COMPILER_PREPROCESSOR
#include <algorithm>
#include <deque>
#include <vector>

#pragma pack(push, _CRT_PACKING)
#pragma warning(push, _STL_WARNING_LEVEL)
#pragma warning(disable : _STL_DISABLED_WARNINGS)
_STL_DISABLE_CLANG_WARNINGS
#pragma push_macro("new")
#undef new

_STD_BEGIN
template <class _Ty, class _Container = deque<_Ty>>
class queue {
public:
    using value_type      = typename _Container::value_type;
    using reference       = typename _Container::reference;
    using const_reference = typename _Container::const_reference;
    using size_type       = typename _Container::size_type;
    using container_type  = _Container;

    static_assert(is_same_v<_Ty, value_type>, "container adaptors require consistent types");

    queue() = default;

    explicit queue(const _Container& _Cont) : c(_Cont) {}

    explicit queue(_Container&& _Cont) noexcept(is_nothrow_move_constructible_v<_Container>) // strengthened
        : c(_STD move(_Cont)) {}

    template <class _Alloc, enable_if_t<uses_allocator_v<_Container, _Alloc>, int> = 0>
    explicit queue(const _Alloc& _Al) noexcept(is_nothrow_constructible_v<_Container, const _Alloc&>) // strengthened
        : c(_Al) {}

    template <class _Alloc, enable_if_t<uses_allocator_v<_Container, _Alloc>, int> = 0>
    queue(const _Container& _Cont, const _Alloc& _Al) : c(_Cont, _Al) {}

    template <class _Alloc, enable_if_t<uses_allocator_v<_Container, _Alloc>, int> = 0>
    queue(_Container&& _Cont, const _Alloc& _Al) noexcept(
        is_nothrow_constructible_v<_Container, _Container, const _Alloc&>) // strengthened
        : c(_STD move(_Cont), _Al) {}

    template <class _Alloc, enable_if_t<uses_allocator_v<_Container, _Alloc>, int> = 0>
    queue(const queue& _Right, const _Alloc& _Al) : c(_Right.c, _Al) {}

    template <class _Alloc, enable_if_t<uses_allocator_v<_Container, _Alloc>, int> = 0>
    queue(queue&& _Right, const _Alloc& _Al) noexcept(
        is_nothrow_constructible_v<_Container, _Container, const _Alloc&>) // strengthened
        : c(_STD move(_Right.c), _Al) {}

    _NODISCARD bool empty() const noexcept(noexcept(c.empty())) /* strengthened */ {
        return c.empty();
    }

    _NODISCARD size_type size() const noexcept(noexcept(c.size())) /* strengthened */ {
        return c.size();
    }

    _NODISCARD reference front() noexcept(noexcept(c.front())) /* strengthened */ {
        return c.front();
    }

    _NODISCARD const_reference front() const noexcept(noexcept(c.front())) /* strengthened */ {
        return c.front();
    }

    _NODISCARD reference back() noexcept(noexcept(c.back())) /* strengthened */ {
        return c.back();
    }

    _NODISCARD const_reference back() const noexcept(noexcept(c.back())) /* strengthened */ {
        return c.back();
    }

    void push(const value_type& _Val) {
        c.push_back(_Val);
    }

    void push(value_type&& _Val) {
        c.push_back(_STD move(_Val));
    }

    template <class... _Valty>
    decltype(auto) emplace(_Valty&&... _Val) {
#if _HAS_CXX17
        return c.emplace_back(_STD forward<_Valty>(_Val)...);
#else // ^^^ C++17 or newer / C++14 vvv
        c.emplace_back(_STD forward<_Valty>(_Val)...);
#endif // _HAS_CXX17
    }

    void pop() noexcept(noexcept(c.pop_front())) /* strengthened */ {
        c.pop_front();
    }

    void swap(queue& _Right) noexcept(_Is_nothrow_swappable<_Container>::value) {
        _Swap_adl(c, _Right.c);
    }

    _NODISCARD const _Container& _Get_container() const noexcept {
        return c;
    }

protected:
    _Container c{};
};

#if _HAS_CXX17
template <class _Container, enable_if_t<!_Is_allocator<_Container>::value, int> = 0>
queue(_Container) -> queue<typename _Container::value_type, _Container>;

template <class _Container, class _Alloc,
    enable_if_t<
        conjunction_v<negation<_Is_allocator<_Container>>, _Is_allocator<_Alloc>, uses_allocator<_Container, _Alloc>>,
        int> = 0>
queue(_Container, _Alloc) -> queue<typename _Container::value_type, _Container>;
#endif // _HAS_CXX17

template <class _Ty, class _Container>
_NODISCARD bool operator==(const queue<_Ty, _Container>& _Left, const queue<_Ty, _Container>& _Right) {
    return _Left._Get_container() == _Right._Get_container();
}

template <class _Ty, class _Container>
_NODISCARD bool operator!=(const queue<_Ty, _Container>& _Left, const queue<_Ty, _Container>& _Right) {
    return _Left._Get_container() != _Right._Get_container();
}

template <class _Ty, class _Container>
_NODISCARD bool operator<(const queue<_Ty, _Container>& _Left, const queue<_Ty, _Container>& _Right) {
    return _Left._Get_container() < _Right._Get_container();
}

template <class _Ty, class _Container>
_NODISCARD bool operator>(const queue<_Ty, _Container>& _Left, const queue<_Ty, _Container>& _Right) {
    return _Left._Get_container() > _Right._Get_container();
}

template <class _Ty, class _Container>
_NODISCARD bool operator<=(const queue<_Ty, _Container>& _Left, const queue<_Ty, _Container>& _Right) {
    return _Left._Get_container() <= _Right._Get_container();
}

template <class _Ty, class _Container>
_NODISCARD bool operator>=(const queue<_Ty, _Container>& _Left, const queue<_Ty, _Container>& _Right) {
    return _Left._Get_container() >= _Right._Get_container();
}

#ifdef __cpp_lib_concepts
template <class _Ty, three_way_comparable _Container>
_NODISCARD compare_three_way_result_t<_Container> operator<=>(
    const queue<_Ty, _Container>& _Left, const queue<_Ty, _Container>& _Right) {
    return _Left._Get_container() <=> _Right._Get_container();
}
#endif // __cpp_lib_concepts

template <class _Ty, class _Container, enable_if_t<_Is_swappable<_Container>::value, int> = 0>
void swap(queue<_Ty, _Container>& _Left, queue<_Ty, _Container>& _Right) noexcept(noexcept(_Left.swap(_Right))) {
    _Left.swap(_Right);
}

template <class _Ty, class _Container, class _Alloc>
struct uses_allocator<queue<_Ty, _Container>, _Alloc> : uses_allocator<_Container, _Alloc>::type {};

template <class _Ty, class _Container = vector<_Ty>, class _Pr = less<typename _Container::value_type>>
class priority_queue {
public:
    using value_type      = typename _Container::value_type;
    using reference       = typename _Container::reference;
    using const_reference = typename _Container::const_reference;
    using size_type       = typename _Container::size_type;
    using container_type  = _Container;
    using value_compare   = _Pr;

    static_assert(is_same_v<_Ty, value_type>, "container adaptors require consistent types");

    priority_queue() = default;

    explicit priority_queue(const _Pr& _Pred) noexcept(
        is_nothrow_default_constructible_v<_Container>&& is_nothrow_copy_constructible_v<value_compare>) // strengthened
        : c(), comp(_Pred) {}

    priority_queue(const _Pr& _Pred, const _Container& _Cont) : c(_Cont), comp(_Pred) {
        _STD make_heap(c.begin(), c.end(), comp);
    }

    priority_queue(const _Pr& _Pred, _Container&& _Cont) : c(_STD move(_Cont)), comp(_Pred) {
        _STD make_heap(c.begin(), c.end(), comp);
    }

    template <class _InIt>
    priority_queue(_InIt _First, _InIt _Last, const _Pr& _Pred, const _Container& _Cont) : c(_Cont), comp(_Pred) {
        c.insert(c.end(), _First, _Last);
        _STD make_heap(c.begin(), c.end(), comp);
    }

    template <class _InIt>
    priority_queue(_InIt _First, _InIt _Last) : c(_First, _Last), comp() {
        _STD make_heap(c.begin(), c.end(), comp);
    }

    template <class _InIt>
    priority_queue(_InIt _First, _InIt _Last, const _Pr& _Pred) : c(_First, _Last), comp(_Pred) {
        _STD make_heap(c.begin(), c.end(), comp);
    }

    template <class _InIt>
    priority_queue(_InIt _First, _InIt _Last, const _Pr& _Pred, _Container&& _Cont) : c(_STD move(_Cont)), comp(_Pred) {
        c.insert(c.end(), _First, _Last);
        _STD make_heap(c.begin(), c.end(), comp);
    }

    template <class _Alloc, enable_if_t<uses_allocator_v<_Container, _Alloc>, int> = 0>
    explicit priority_queue(const _Alloc& _Al) noexcept(is_nothrow_constructible_v<_Container, const _Alloc&>&&
            is_nothrow_default_constructible_v<value_compare>) // strengthened
        : c(_Al), comp() {}

    template <class _Alloc, enable_if_t<uses_allocator_v<_Container, _Alloc>, int> = 0>
    priority_queue(const _Pr& _Pred, const _Alloc& _Al) noexcept(is_nothrow_constructible_v<_Container, const _Alloc&>&&
            is_nothrow_copy_constructible_v<value_compare>) // strengthened
        : c(_Al), comp(_Pred) {}

    template <class _Alloc, enable_if_t<uses_allocator_v<_Container, _Alloc>, int> = 0>
    priority_queue(const _Pr& _Pred, const _Container& _Cont, const _Alloc& _Al) : c(_Cont, _Al), comp(_Pred) {
        _STD make_heap(c.begin(), c.end(), comp);
    }

    template <class _Alloc, enable_if_t<uses_allocator_v<_Container, _Alloc>, int> = 0>
    priority_queue(const _Pr& _Pred, _Container&& _Cont, const _Alloc& _Al) : c(_STD move(_Cont), _Al), comp(_Pred) {
        _STD make_heap(c.begin(), c.end(), comp);
    }

    template <class _Alloc, enable_if_t<uses_allocator_v<_Container, _Alloc>, int> = 0>
    priority_queue(const priority_queue& _Right, const _Alloc& _Al) : c(_Right.c, _Al), comp(_Right.comp) {}

    template <class _Alloc, enable_if_t<uses_allocator_v<_Container, _Alloc>, int> = 0>
    priority_queue(priority_queue&& _Right, const _Alloc& _Al) noexcept(
        is_nothrow_constructible_v<_Container, _Container, const _Alloc&>&&
            is_nothrow_move_constructible_v<value_compare>) // strengthened
        : c(_STD move(_Right.c), _Al), comp(_STD move(_Right.comp)) {}

    _NODISCARD bool empty() const noexcept(noexcept(c.empty())) /* strengthened */ {
        return c.empty();
    }

    _NODISCARD size_type size() const noexcept(noexcept(c.size())) /* strengthened */ {
        return c.size();
    }

    _NODISCARD const_reference top() const noexcept(noexcept(c.front())) /* strengthened */ {
        return c.front();
    }

    void push(const value_type& _Val) {
        c.push_back(_Val);
        _STD push_heap(c.begin(), c.end(), comp);
    }

    void push(value_type&& _Val) {
        c.push_back(_STD move(_Val));
        _STD push_heap(c.begin(), c.end(), comp);
    }

    template <class... _Valty>
    void emplace(_Valty&&... _Val) {
        c.emplace_back(_STD forward<_Valty>(_Val)...);
        _STD push_heap(c.begin(), c.end(), comp);
    }

    void pop() {
        _STD pop_heap(c.begin(), c.end(), comp);
        c.pop_back();
    }

    void swap(priority_queue& _Right) noexcept(
        _Is_nothrow_swappable<_Container>::value&& _Is_nothrow_swappable<_Pr>::value) {
        _Swap_adl(c, _Right.c);
        _Swap_adl(comp, _Right.comp);
    }

protected:
    _Container c{};
    _Pr comp{};
};

#if _HAS_CXX17
template <class _Pr, class _Container,
    enable_if_t<conjunction_v<negation<_Is_allocator<_Pr>>, negation<_Is_allocator<_Container>>>, int> = 0>
priority_queue(_Pr, _Container) -> priority_queue<typename _Container::value_type, _Container, _Pr>;

template <class _Iter, class _Pr = less<_Iter_value_t<_Iter>>, class _Container = vector<_Iter_value_t<_Iter>>,
    enable_if_t<conjunction_v<_Is_iterator<_Iter>, negation<_Is_allocator<_Pr>>, negation<_Is_allocator<_Container>>>,
        int> = 0>
priority_queue(_Iter, _Iter, _Pr = _Pr(), _Container = _Container())
    -> priority_queue<_Iter_value_t<_Iter>, _Container, _Pr>;

template <class _Pr, class _Container, class _Alloc,
    enable_if_t<conjunction_v<negation<_Is_allocator<_Pr>>, negation<_Is_allocator<_Container>>, _Is_allocator<_Alloc>,
                    uses_allocator<_Container, _Alloc>>,
        int> = 0>
priority_queue(_Pr, _Container, _Alloc) -> priority_queue<typename _Container::value_type, _Container, _Pr>;
#endif // _HAS_CXX17

template <class _Ty, class _Container, class _Pr,
    enable_if_t<_Is_swappable<_Container>::value && _Is_swappable<_Pr>::value, int> = 0>
void swap(priority_queue<_Ty, _Container, _Pr>& _Left, priority_queue<_Ty, _Container, _Pr>& _Right) noexcept(
    noexcept(_Left.swap(_Right))) {
    _Left.swap(_Right);
}

template <class _Ty, class _Container, class _Pr, class _Alloc>
struct uses_allocator<priority_queue<_Ty, _Container, _Pr>, _Alloc> : uses_allocator<_Container, _Alloc>::type {};

_STD_END

#pragma pop_macro("new")
_STL_RESTORE_CLANG_WARNINGS
#pragma warning(pop)
#pragma pack(pop)
#endif // _STL_COMPILER_PREPROCESSOR
#endif // _QUEUE_