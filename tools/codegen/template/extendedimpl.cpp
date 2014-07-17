namespace LuaQt{
	class /*%return class.classname%*/_Extended_Impl
		: public /*%return class.classname%*/
	{
	public:
/*%
	return constructorOverloads()
%*/

		~/*%return class.classname%*/_Extended_Impl()
		{
			mo = NULL;
		}

		virtual const QMetaObject *metaObject() const
		{
			return (mo);
		}

		// just use super class's qt_metacast for C++ class wrapping.
		/*virtual void *qt_metacast(const char *)
		{
		
		}*/

		virtual int qt_metacall(QMetaObject::Call _c, int _id, void ** _a)
		{
			_id = /*%return class.classname%*/::qt_metacall(_c, _id, _a);
			if (_id < 0)
				return _id;
			if (_c == QMetaObject::InvokeMetaMethod) {
				int mc = mo->d.data[4];
				if (_id < mc) {
					LuaQt::generic_callback* mc = reinterpret_cast<LuaQt::generic_callback*>(mo->d.extradata);
					Q_ASSERT_X(mc, "qt_metacall", "No metacall function provided");
					lua_State *L = mc->getState();
					mc->push();
					lua_pushinteger(L, (int)_c);
					lua_pushinteger(L, _id+1);
					LuaQt::PushObject(L, this);
					lua_pushlightuserdata(L, _a);
					lua_call(L, 4, 0);
				}
				_id -= mc;
			} else if (_c == QMetaObject::RegisterMethodArgumentMetaType){
				int mc = mo->d.data[4];
				if (_id < mc) {
					Q_ASSERT_X(false, "qt_metacall", "Not Implemented.");
				}
				_id -= mc;
			}
			return _id;
		}

	private:
		const QMetaObject * mo;
	};
}

#define CLASS_EXTENDED LuaQt::/*%return class.classname%*/_Extended_Impl