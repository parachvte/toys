<?php

class A {
	/**
	 *
	 * a: b
	 * c: d e ..\n
	 * c: xxxxxx
	 *
	 * x: 123123
	 * rule : 12 213123 213 4190
	 * rule : 21
	 * @needLogin
	 *
	 * aaa bbb ccc
	 */
	function b() {

	}

	/**
	 * abbcc @needLogin
	 * @needlogin
	 */
	function c() {

	}
}


class Annotate {
	/**
	 * @param $class
	 * @param $method
	 * @return string
	 */
	private static function getDocComment($class, $method) {
		$methodMeta = new ReflectionMethod($class, $method);
		return $methodMeta->getDocComment();
	}

	/**
	 * @param $docLine
	 * @return bool|string
	 */
	private static function getRealComment($docLine) {
		if (strpos($docLine, '/**') === 0) return false; // ignore the first line
		$realComment = trim(explode('*', $docLine, 2)[1]);
		if (empty($realComment) || $realComment === '/') false; // ignore empty line or last line
		return $realComment;
	}

	/**
	 * @param $class
	 * @param $method
	 * @param $replicated
	 * @return array
	 */
	private static function _get($class, $method, $replicated) {
		$docDict = array();
		$docList = explode(PHP_EOL, Annotate::getDocComment($class, $method));
		foreach ($docList as $docLine) {
			if (!($realComment = Annotate::getRealComment($docLine))) continue;

			$key = explode(' ', $realComment, 2)[0];
			$value = strpos($realComment, ':') ? trim(explode(':', $realComment)[1]) : null;

			if (!$replicated) {
				if (!isset($docDict[$key])) $docDict[$key] = $value;
			} else {
				if (!isset($docDict[$key])) $docDict[$key] = array();
				$docDict[$key][] = $value;
			}
		}
		return $docDict;
	}

	/**
	 * @param $class
	 * @param $method
	 * @return array
	 */
	public static function get($class, $method) {
		return Annotate::_get($class, $method, false);
	}

	/**
	 * @param $class
	 * @param $method
	 * @return array
	 */
	public static function getAll($class, $method) {
		return Annotate::_get($class, $method, true);
	}

	/**
	 * return true if there is a annotation key named rule, has a tagged value $rule
	 */
	public static function hasRule($class, $method, $rule) {
		$docDict = Annotate::getAll($class, $method);
		if (isset($docDict['rule'])) {
			foreach ($docDict['rule'] as $value) {
				if (in_array($rule, explode(' ', $value))) return true;
			}
		}
		return false;
	}

	/**
	 * return true if there is a annotation key named @needLogin
	 */
	public static function needLogin($class, $method) {
		return isset(Annotate::getAll($class, $method)['@needLogin']);
	}
}

$anno = new Annotate();
var_dump($anno->get('A', 'b'));
var_dump($anno->getAll('A', 'b'));
var_dump($anno->hasRule('A', 'b', '12')); // true
var_dump($anno->hasRule('A', 'b', '21')); // true
var_dump($anno->hasRule('A', 'b', '19')); // false
var_dump($anno->needLogin('A', 'b')); // true
var_dump($anno->needLogin('A', 'c')); // false
