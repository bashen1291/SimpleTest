import lldb
import lldb.formatters.Logger 

lldb.formatters.Logger._lldb_formatters_debug_level = 0
_max_capping_size = 255

def DictLey_SummaryProvider(valobj, internal_dict):
    logger = lldb.formatters.Logger.Logger()
    try:
        if valobj.GetChildMemberWithName('_type').GetValueAsUnsigned() == 0:
            return 'null'
        if valobj.GetChildMemberWithName('_type').GetValueAsUnsigned() == 1:
            return valobj.GetChildMemberWithName('_integer').GetValueAsSigned()
        len = valobj.GetChildMemberWithName('_length').GetValueAsUnsigned()
        str = '"'
        arr = None
        if len >= 32:
            arr = valobj.GetChildMemberWithName('_string').GetPointeeData(0, len).uint8;
        else:
            arr = valobj.GetChildMemberWithName('_buffer').GetPointeeData(0, len).uint8;
        for c in arr:
            str = str + unichr(c)
        str = str + '"'
        return str.encode('utf-8')
    except:
        return ''

class chash_SyntheticProvider:

    def __init__(self, valobj, internal_dict):
        logger = lldb.formatters.Logger.Logger()
        try:
            self.valobj = valobj
            self.root = None
            self.count = None
            self.zero = None
            self.index_type = None
            self.value_type = None
            logger >> "Providing synthetic children for a chash named " + str(valobj.GetName())
        except:
            pass
        
    def has_children(self):
        return True
    
    def update(self):
        logger = lldb.formatters.Logger.Logger()
        try:
            self.root = self.valobj.GetChildMemberWithName('root_')
            
            s1 = self.root.GetChildMemberWithName('size').GetValueAsUnsigned()
            s2 = self.root.GetChildMemberWithName('free_count').GetValueAsUnsigned()
            self.count = s1 - s2
            
            if self.count > _max_capping_size:
                logger >> "broken container by size " + str(self.count)
                self.count = 0
            
            self.index_type = self.root.GetChildMemberWithName('index').GetType().GetPointeeType()
            self.value_type = self.root.GetChildMemberWithName('value').GetType().GetPointeeType().GetFieldAtIndex(0).GetType().GetTemplateArgumentType(0)
            
            hash_size = self.index_type.GetFieldAtIndex(0).GetType().GetByteSize()

            if hash_size == 1:
                self.zero = 255
            elif hash_size == 2:
                self.zero = 65536
            elif hash_size == 4:
                self.zero = 4294967295
            else:
                self.zero = 18446744073709551615
        except:
            pass
    
    def num_children(self):
        logger = lldb.formatters.Logger.Logger()
        return self.count

    def get_child_index(self,name):
        logger = lldb.formatters.Logger.Logger()
        try:
            return int(name.lstrip('[').rstrip(']'))
        except:
            return -1

    def get_child_at_index(self,index):
        logger = lldb.formatters.Logger.Logger()
        try:
            if index < 0:
                return None
            if index >= self.num_children():
                return None
            if self.valobj.IsValid() == False:
                return None
            i = 0
            c = index
            while self.get_slot_valid(i) == False:
                i += 1
            while c > 0:
                if self.get_slot_valid(i):
                    c -= 1
                i += 1
            return self.root.GetChildMemberWithName('value').CreateChildAtOffset('[' + str(index) + ']', i * self.value_type.GetByteSize(), self.value_type)
        except:
            return None
            
    def get_slot_valid(self,slot):
        return self.root.GetChildMemberWithName('index').CreateChildAtOffset(None, slot * self.index_type.GetByteSize(), self.index_type).GetChildMemberWithName('hash').GetChildMemberWithName('hash').GetValueAsUnsigned() != self.zero
        
        
class bpptree_SyntheticProvider:

    def __init__(self, valobj, internal_dict):
        logger = lldb.formatters.Logger.Logger()
        try:
            self.valobj = valobj
            self.root = None
            self.count = None
            self.leaf_type = None
            self.value_type = None
            logger >> "Providing synthetic children for a bpptree named " + str(valobj.GetName())
        except:
            pass
        
    def has_children(self):
        return True
    
    def update(self):
        logger = lldb.formatters.Logger.Logger()
        try:
            self.root = self.valobj.GetChildMemberWithName('root_')

            self.count = self.root.GetChildMemberWithName('parent').GetChildMemberWithName('size').GetValueAsUnsigned()
            
            if self.count > _max_capping_size:
                logger >> "broken container by size " + str(self.count)
                self.count = 0
                
            self.leaf_type = self.root.GetType().GetTemplateArgumentType(0).GetPointerType()
            self.value_type = self.root.GetType().GetTemplateArgumentType(1)
        except:
            pass
    
    def num_children(self):
        logger = lldb.formatters.Logger.Logger()
        return self.count

    def get_child_index(self,name):
        logger = lldb.formatters.Logger.Logger()
        try:
            return int(name.lstrip('[').rstrip(']'))
        except:
            return -1

    def get_child_at_index(self,index):
        logger = lldb.formatters.Logger.Logger()
        try:
            if index < 0:
                return None
            if index >= self.num_children():
                return None
            if self.valobj.IsValid() == False:
                return None
            node = self.root.GetChildMemberWithName('left').Cast(self.leaf_type)
            c = index
            s = node.GetChildMemberWithName('size').GetValueAsUnsigned()
            while c >= s:
                c -= s
                node = node.GetChildMemberWithName('next').Cast(self.leaf_type)
                s = node.GetChildMemberWithName('size').GetValueAsUnsigned()
            return node.GetChildMemberWithName('item').CreateChildAtOffset('[' + str(index) + ']', c * self.value_type.GetByteSize(), self.value_type)
        except:
            logger >> 'except'
            return None

class ccArray_SyntheticProvider:

    def __init__(self, valobj, internal_dict):
        logger = lldb.formatters.Logger.Logger()
        try:
            self.valobj = valobj
            self.count = None
            logger >> "Providing synthetic children for a ccArray named " + str(valobj.GetName())
        except:
            pass
        
    def has_children(self):
        return True
    
    def update(self):
        logger = lldb.formatters.Logger.Logger()
        try:
            self.count = self.valobj.GetChildMemberWithName('num').GetValueAsSigned()
            self.type = self.valobj.GetChildMemberWithName('arr').GetType().GetPointeeType()
        except:
            pass
    
    def num_children(self):
        logger = lldb.formatters.Logger.Logger()
        return self.count

    def get_child_index(self,name):
        try:
            return int(name.lstrip('[').rstrip(']'))
        except:
            return -1

    def get_child_at_index(self,index):
        logger = lldb.formatters.Logger.Logger()
        try:
            if index < 0:
                return None
            if index >= self.num_children():
                return None
            if self.valobj.IsValid() == False:
                return None
            return self.valobj.GetChildMemberWithName('arr').CreateChildAtOffset('[' + str(index) + ']', index * self.type.GetByteSize(), self.type)
        except:
            pass