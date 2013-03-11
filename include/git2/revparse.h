/*
 * Copyright (C) the libgit2 contributors. All rights reserved.
 *
 * This file is part of libgit2, distributed under the GNU GPL v2 with
 * a Linking Exception. For full terms see the included COPYING file.
 */
#ifndef INCLUDE_git_revparse_h__
#define INCLUDE_git_revparse_h__

#include "common.h"
#include "types.h"


/**
 * @file git2/revparse.h
 * @brief Git revision parsing routines
 * @defgroup git_revparse Git revision parsing routines
 * @ingroup Git
 * @{
 */
GIT_BEGIN_DECL

/**
 * Find an object, as specified by a revision string. See `man gitrevisions`, or the documentation
 * for `git rev-parse` for information on the syntax accepted.
 *
 * @param out pointer to output object
 * @param repo the repository to search in
 * @param spec the textual specification for an object
 * @return 0 on success, GIT_ENOTFOUND, GIT_EAMBIGUOUS,
 * GIT_EINVALIDSPEC or an error code
 */
GIT_EXTERN(int) git_revparse_single(git_object **out, git_repository *repo, const char *spec);

/**
 * Parse a string with the form of a revision range, as accepted by
 * `git rev-list`, `git diff`, and others.
 *
 * @param left (output) the left-hand commit
 * @param right (output) the right-hand commit
 * @param threedots (output) 0 if the endpoints are separated by two dots, 1 if by three
 * @param repo the repository to find the commits in
 * @param rangelike the rangelike string to be parsed
 * @return 0 on success, or any error `git_revparse_single` can return
 */
GIT_EXTERN(int) git_revparse_rangelike(git_object **left, git_object **right, int *threedots, git_repository *repo, const char *rangelike);


/**
 * Revparse flags.  These indicate the intended behavior of the spec passed to
 * git_revparse.
 */
typedef enum {
  /** The spec targeted a single object. */
  GIT_REVPARSE_SINGLE         = 1 << 0,
  /** The spec targeted a range of commits. */
  GIT_REVPARSE_RANGE          = 1 << 1,
  /** The spec used the '...' operator, which invokes special semantics. */
  GIT_REVPARSE_MERGE_BASE     = 1 << 2,
} git_revparse_flag_t;


/**
 * Find an object or range of commits as specified by a revision string.
 * See `man gitrevisions` or http://git-scm.com/docs/git-rev-parse.html#_specifying_revisions
 * for information on the syntax accepted.
 *
 * @param left buffer that receives the target of the left side of a range operator. If
 *             there is no range operator, this buffer receives the single target.
 * @param right buffer that receives the target of the right side of a range operator.
 *              This is only filled in if `spec` specifies a range of commits
 * @param flags buffer that receives a bitwise combination of `git_revparse_flag_t` values
 * @param repo the repository to search in
 * @param spec the rev-parse spec to parse
 * @return 0 on success, GIT_INVALIDSPEC, GIT_ENOTFOUND, GIT_EAMBIGUOUS or an error code
 */
GIT_EXTERN(int) git_revparse(
  git_oid *left,
  git_oid *right,
  unsigned int *flags,
  git_repository *repo,
  const char *spec);


/** @} */
GIT_END_DECL
#endif
